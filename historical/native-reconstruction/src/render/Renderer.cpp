// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Renderer.hpp"
#include "render/AlphaAnimationLifecycle.hpp"
#include "render/FrameRegionPreparation.hpp"
#include "render/FrameTerrainRequests.hpp"
#include "render/FrameDepthRefresh.hpp"
#include "render/TerrainDepthPass.hpp"
#include "render/FramePlane.hpp"
#include "render/ShadowKeys.hpp"
#include "render/StaticRedraw.hpp"
#include "sim/FootCoordinates.hpp"
#include "sim/BuildingCoordinates.hpp"
#include <new>
#include "assets/PreparedData.hpp"
#include "assets/BuildingDepthImage.hpp"
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include "render/UnitBaseDepth.hpp"
#include "render/TacticalViewportMatrix.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <fstream>
#include <numeric>

namespace ra2 {
namespace {
const Matrix& suppliedTacticalInverse(){
    static const Matrix inverse={256.f/60.f,256.f/30.f,0,0,-256.f/60.f,256.f/30.f,0,0,0,0,1,0};
    return inverse;
}
}
Renderer::Renderer(const GameAssets& assets,int w,int h,const std::string& playerColor,int detail):assets_(assets),detail_(detail),width(w),height(h),pixels(std::size_t(w)*h) {
    if(w<=0||h<=0||w>4096||h>4096) throw std::runtime_error("Invalid framebuffer size");
    if(detail<0||detail>2)throw std::runtime_error("Graphics detail must be 0..2");
    if(assets.hasPlacedLights&&!assets.placedLight)throw std::runtime_error("Unsupported placed emitter; only one stock INGALITE is recovered");
    if(assets.sceneryLifecycle.occupation.members.size()!=assets.scenery.size())throw std::runtime_error("Prepare ordinary scenery lifecycle before rendering");
    for(const auto& [id,member]:assets.sceneryLifecycle.occupation.members)sceneryDrawStates_[id]=member.state;
    lightSettings_=mapLightSettings(assets.map.ambient,assets.map.tint,assets.map.ground,assets.map.level);
    extraUnitLight_=extraUnitLight(assets.extraUnitLight);
    for(const auto& c:assets.map.cells)mapLights_.push_back(cellLight(assets.renderData,lightSettings_,c.x,c.y,c.z));
    if(assets.engineDataSource==PatchedEngineSha){
        unitWorld_.unit.pool.bytes.resize(0x80000);
        for(const auto& c:assets.map.cells)
            unitDepthCells_.push_back({{std::int16_t(c.x),std::int16_t(c.y)},0,65535,0,-1,0});
    }
    heightScale_=worldHeightScale(assets.rasterData,assets.renderData);
    if(assets.preparedTerrain){
        terrainView_=std::make_unique<TerrainMapView>(assets.preparedTerrain);
        rampPoseData_=readRampPoseData(readFile(preparedDataPath(assets.engineDataSource,"ramp-pose-data.bin")),assets.engineDataSource);
        const auto geometry=stockRampGeometry(assets.renderData,assets.rasterData,assets.driveData->directionsToTargets,
            readRampGeometryData(readFile(preparedDataPath(assets.engineDataSource,"ramp-geometry-data.bin")),assets.engineDataSource));
        rampMatrices_=voxelRampShadowMatrices(assets.rasterData,geometry.axisTilt,geometry.diagonalTilt);
        rampQuaternions_=voxelRampQuaternions(assets.rasterData,assets.renderData,geometry.axisTilt,geometry.diagonalTilt);
    }
    stagingRemap_=stagingRemap(assets.stagingPalette,assets.stagingPalette);
    // Supplied registry: named colors represent the prototype's one house.
    // Original house creation/ID assignment and converter lifetime remain open.
    for(const auto& [name,color]:assets.playerColors)houseConverters_.push_back(unitLightConverter(assets.rasterData,assets.renderData,assets.unitPalette,color));
    setPlayerColor(playerColor);
    if(assets.placedLight){installStaticLight(assets.placedLight->first,assets.placedLight->second);setLightActive(true);}
}
void Renderer::installStaticLight(int x,int y) {
    if(staticLight_)throw std::runtime_error("Only one static light is supported");
    const auto* c=assets_.cell(x,y);if(!c||!assets_.invisibleLight)throw std::runtime_error("Missing stock INGALITE or valid placement cell");
    const auto& raw=*assets_.invisibleLight;
    const auto type=lightTypeInputs(raw.radius,raw.intensity,raw.tint);
    // Original building creation skips the source when integer intensity is zero.
    if(type.intensity==0)return;
    staticLight_=makeStaticLight(type,x*256+128,y*256+128,c->z*104);
}
void Renderer::addLightDemo(int x,int y) {installStaticLight(x,y);setLightActive(true);}
std::size_t Renderer::setLightActive(bool active) {
    if(!staticLight_||!changeLightActive(*staticLight_,active))return 0;
    const auto visits=affectedLightCells(assets_.renderData,*staticLight_,assets_.map.cells,detail_);
    for(auto i:visits) {
        const auto& c=assets_.map.cells[i];
        mapLights_[i]=cellLight(assets_.renderData,lightSettings_,c.x,c.y,c.z,std::span(&*staticLight_,1),detail_);
    }
    // Whole-terrain cache invalidation is a native display adapter. The original
    // immediate source routine notifies map redraw; its regional lifetime is open.
    if(!visits.empty())valid_=false;lightUpdates_+=visits.size();return visits.size();
}
void Renderer::setPlayerColor(const std::string& name) {
    const auto color=lower(name);const auto it=assets_.playerColors.find(color);
    if(it==assets_.playerColors.end())throw std::invalid_argument("Unknown rules player color: "+name);
    houseScheme_=std::size_t(std::distance(assets_.playerColors.begin(),it));
    playerColor_=color;
}
std::int16_t Renderer::buildingAmbient(int identity,TerrainCellPoint point)const{
    if(identity<0||std::size_t(identity)>=assets_.map.cells.size())
        throw std::invalid_argument("Unbound Building fallback ambient owner");
    const auto& source=assets_.map.cells[std::size_t(identity)];
    if(source.x!=point.x||source.y!=point.y)
        throw std::invalid_argument("Building Cell/light owner association differs");
    return std::bit_cast<std::int16_t>(std::uint16_t(mapLights_.at(std::size_t(identity)).ambient));
}
const CellLight& Renderer::lightingAt(const MapCell& c) const {return mapLights_.at(assets_.cellIndex.at({c.x,c.y}));}
int Renderer::unitBrightnessAt(const MapCell& c) const {return ordinaryUnitBrightness(std::int16_t(lightingAt(c).ambient),extraUnitLight_);}
const std::vector<Palette16>& Renderer::terrainPalettes(std::array<int,3> tint) {
    // Native value-keyed terrain storage; original ownership/lifetime remains open.
    const auto converter=terrainConverterInputs(tint,detail_);tint=converter.tint;
    auto& cache=terrainPalettes_;auto it=cache.find(tint);
    if(it==cache.end()) {
        std::array<std::uint8_t,256> affected;affected.fill(1);
        it=cache.emplace(tint,lightPalette(assets_.renderData,assets_.terrainPalette,tint,converter.shades,affected)).first;
    }
    return it->second;
}
PixelPoint Renderer::viewportOrigin() const {
    const int w=int(std::ceil(width/camera.zoom)),h=int(std::ceil(height/camera.zoom));
    const int x=int(std::lround(camera.x)),y=int(std::lround(camera.y));
    if(tacticalWidth_!=w||tacticalHeight_!=h||tacticalViewport_.centerX!=x||tacticalViewport_.centerY!=y){
        tacticalViewport_.centerX=x;tacticalViewport_.centerY=y;
        // Supplied planar inverse coefficients. Transform591380 reuses the
        // recovered point kernel; original matrix initialization remains open.
        updateTacticalViewportMatrix(tacticalViewport_,w,h,suppliedTacticalInverse());
        tacticalWidth_=w;tacticalHeight_=h;
    }
    return {tacticalViewport_.originX,tacticalViewport_.originY};
}
CellRedrawView Renderer::cellRedrawView()const{
    const auto origin=viewportOrigin();
    return {0,origin.x,origin.y,0,0,tacticalWidth_,tacticalHeight_};
}
bool Renderer::buildingRedrawPending(PixelRect viewport,const BuildingFrameRegistry& buildings)const{
    return buildingRedrawInFrame(viewportOrigin(),viewport,heightScale_,buildings);
}
void Renderer::requestBuildingDraws(const CellRedrawQueue& cells,const std::function<TerrainCellPoint(int)>& point,
        const PixelRect& first,const PixelRect& second,std::int32_t full,const StaticRedrawScan& scan)const{
    const auto view=cellRedrawView();
    const PixelRect viewport{view.viewportX,view.viewportY,view.viewportWidth,view.viewportHeight};
    BuildingRedrawRequestServices s;
    s.cellCount=[&]{return cells.countE0;};
    s.cellAt=[&](int i){if(!point)throw std::invalid_argument("Building redraw Cell owner unbound");return point(cells.cells.at(std::size_t(i)));};
    s.dirtyCount=[this]{return frameDirtyRegions_.count;};
    s.dirtyAt=[this](int i){return frameDirtyRegions_.slots.at(std::size_t(i)).bounds;};
    s.project6a27a0=[this](Coord p){return worldPixels(heightScale_,p);};s.scan6a9f60=scan;
    requestBuildingRedraw(tacticalViewport_.originX,tacticalViewport_.originY,viewport,first,second,full,s);
}
void Renderer::requestTerrainDraws(const CellRedrawQueue& cells,const std::function<Coord(int)>& center,
        const PixelRect& first,const PixelRect& second,const PixelRect& clip,std::int32_t full,
        const std::function<bool()>& present,const std::function<void(int,PixelPoint,const PixelRect&)>& terrain,
        const std::function<void(PixelPoint,const PixelRect&)>& animation,
        const std::function<void(const PixelRect&)>& rectangle,const FillStoreTrace& stores){
    const auto view=cellRedrawView();const PixelRect viewport{view.viewportX,view.viewportY,view.viewportWidth,view.viewportHeight};
    FrameTerrainServices s;s.cellCount=[&]{return cells.countE0;};
    s.cellAt=[&](int i){return cells.cells.at(std::size_t(i));};s.center475d60=center;
    s.project6a27a0=[this](Coord p){return worldPixels(heightScale_,p);};
    s.dirtyCount=[this]{return frameDirtyRegions_.count;};
    s.dirtyBacking=[this]{return std::span<DirtyRegion>(frameDirtyRegions_.slots);};
    s.terrainPresent=present;s.terrain475520=terrain;s.animation41f1c0=animation;s.rectangle6a7820=rectangle;
    s.alpha4110b0=[&](const PixelRect& r){refreshFrameAlpha(r,stores);};
    requestFrameTerrain(tacticalViewport_.originX,tacticalViewport_.originY,viewport,first,second,clip,full,s);
}
void Renderer::refreshFrameAlpha(PixelRect r,const FillStoreTrace& stores){
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=alpha_.size()||alpha_.size()>UINT32_MAX/2)
        throw std::invalid_argument("Frame alpha plane not prepared");
    const std::uint32_t begin=0,end=std::uint32_t(alpha_.size()*2),extent=end,buffer=0;const std::int32_t bpp=2;
    const auto surface=[&]{return SurfacePixelView{renderWidth_,terrainAlphaLock_,bpp,buffer,{},alpha_,true};};
    FrameDepthServices s;s.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y);};
    s.unlock60=[&]{unlockSurfacePixels(surface());};
    ra2::refreshFrameAlpha({frameAlphaOffset_,begin,end,extent,renderWidth_,{{},alpha_}},r,s,stores);
}
void Renderer::drawVisibilityMask(bool fog,const PixelPoint& point,const PixelRect& clip,std::int32_t frame,
        const std::function<std::uint32_t()>& scenarioFlags,const FillStoreTrace& stores){
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=alpha_.size()||alpha_.size()>UINT32_MAX/2)
        throw std::invalid_argument("Visibility alpha plane not prepared");
    const std::uint32_t begin=0,end=std::uint32_t(alpha_.size()*2),extent=end,buffer=0;const std::int32_t bpp=2;
    const auto surface=[&]{return SurfacePixelView{renderWidth_,terrainAlphaLock_,bpp,buffer,{},alpha_,true};};
    const auto view=[&]{return FrameDepthView{frameAlphaOffset_,begin,end,extent,renderWidth_,{{},alpha_}};};
    FrameDepthServices address;address.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y);};
    address.unlock60=[&]{unlockSurfacePixels(surface());};
    VisibilityRasterServices s;
    s.load5956c0=[&](std::string_view name){
        auto key=std::string(name);auto it=visibilityRasterImages_.find(key);
        if(it==visibilityRasterImages_.end())it=visibilityRasterImages_.emplace(key,assets_.store.require(key)).first;
        return std::span<const std::uint8_t>(it->second.ptr(),it->second.size);};
    s.scenarioFlags=scenarioFlags;s.alpha=view;s.viewportY=[&]{return cellRedrawView().viewportY;};
    s.address411230=[&](PixelPoint p){return framePlaneAddress(view(),p,address);};
    drawVisibilityRaster(fog,visibilityRasterCache_,point,clip,frame,s,stores);
}
AlphaAnimationRecord* Renderer::constructAlphaAnimation(AlphaAnimationRecord& r,const void* associated,
        std::int32_t x,std::int32_t y,bool defaultConstructor,const AlphaAnimationLifecycleServices& s){
    return ra2::constructAlphaAnimation(r,alphaCombination_,associated,x,y,defaultConstructor,s);
}
void Renderer::cleanupAlphaAnimations(const AlphaAnimationLifecycleServices& s){
    ra2::cleanupAlphaAnimations(alphaCombination_,s.primary.entries,
        [&](AlphaAnimationRecord& r,std::uint32_t deleting){deleteAlphaAnimation(r,deleting,s);},s.store);
}
void Renderer::drawAlphaAnimations(bool pointPass,const PixelPoint& point,const PixelRect& clip,
        AlphaAnimationServices s,const FillStoreTrace& stores){
    if(!alphaCombination_.initialized)throw std::invalid_argument("Alpha animation table startup unbound");
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=alpha_.size()||alpha_.size()>UINT32_MAX/2)
        throw std::invalid_argument("Animation alpha plane not prepared");
    const std::uint32_t begin=0,end=std::uint32_t(alpha_.size()*2),extent=end,buffer=0;const std::int32_t bpp=2;
    const auto surface=[&]{return SurfacePixelView{renderWidth_,terrainAlphaLock_,bpp,buffer,{},alpha_,true};};
    const auto view=[&]{return FrameDepthView{frameAlphaOffset_,begin,end,extent,renderWidth_,{{},alpha_}};};
    FrameDepthServices address;address.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y);};
    address.unlock60=[&]{unlockSurfacePixels(surface());};
    s.origin=[&]{return PixelPoint{tacticalViewport_.originX,tacticalViewport_.originY};};
    s.viewport=[&]{const auto v=cellRedrawView();return PixelPoint{v.viewportX,v.viewportY};};
    s.alpha=view;s.address411230=[&](PixelPoint p){return framePlaneAddress(view(),p,address);};
    ra2::drawAlphaAnimations(pointPass,point,clip,alphaCombination_,s,stores);
}
void Renderer::drawVisibilityRectangle(const PixelRect& requested,RectangularVisibilityServices s){
    const auto view=cellRedrawView();const PixelRect viewport{view.viewportX,view.viewportY,view.viewportWidth,view.viewportHeight};
    s.project6a27a0=[this](Coord p){return worldPixels(heightScale_,p);};
    drawRectangularVisibility({tacticalViewport_.originX,tacticalViewport_.originY,viewport,suppliedTacticalInverse()},requested,s);
}
void Renderer::prepareFrameRegions(const CellRedrawQueue& cells,const std::function<Coord(int)>& center,
        std::int32_t full,std::int32_t dx,std::int32_t dy,const PixelRect& clip,
        const std::function<void(const PixelRect&)>& depth,const std::function<bool()>& present,
        const std::function<void(int,PixelPoint,const PixelRect&)>& terrain){
    const auto view=cellRedrawView();const PixelRect viewport{view.viewportX,view.viewportY,view.viewportWidth,view.viewportHeight};
    FrameRegionServices s;s.dirtyCount=[this]{return frameDirtyRegions_.count;};
    s.setDirtyCount=[this](int n){frameDirtyRegions_.count=n;};
    s.dirtyBacking=[this]{return std::span<DirtyRegion>(frameDirtyRegions_.slots);};
    s.cellCount=[&]{return cells.countE0;};s.cellAt=[&](int i){return cells.cells.at(std::size_t(i));};
    s.center475d60=center;s.project6a27a0=[this](Coord p){return worldPixels(heightScale_,p);};
    s.depth7761c0=depth;s.terrainPresent=present;s.terrain4754b0=terrain;
    ra2::prepareFrameRegions(tacticalViewport_.originX,tacticalViewport_.originY,viewport,full,dx,dy,clip,s);
}
void Renderer::refreshFrameDepth(PixelRect r,const FillStoreTrace& stores){
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=depth_.size()||depth_.size()>UINT32_MAX/2)
        throw std::invalid_argument("Frame depth plane not prepared");
    ++frameDepthRefreshCalls;
    // Supplied allocation/startup; explicit recovered scrolling owns its offset.
    // Borrow the current depth vector,
    // actual raster width and one persistent lock field; no parallel surface.
    const std::uint32_t begin=0,end=std::uint32_t(depth_.size()*2),extent=end,buffer=0;
    const std::int32_t bpp=2;
    const auto surface=[&]{return SurfacePixelView{renderWidth_,frameDepthLock_,bpp,buffer,{},depth_,true};};
    FrameDepthServices s;s.lock5c=[&](int x,int y){return lockSurfacePixels(surface(),x,y);};
    s.unlock60=[&]{unlockSurfacePixels(surface());};
    ra2::refreshFrameDepth({frameDepthOffset_,begin,end,extent,renderWidth_,{{},depth_}},r,s,stores);
}
void Renderer::prepareFrameRegions(const CellRedrawQueue& cells,const std::function<Coord(int)>& center,
        std::int32_t full,std::int32_t dx,std::int32_t dy,const PixelRect& clip,
        const std::function<bool()>& present,const std::function<void(int,PixelPoint,const PixelRect&)>& terrain){
    prepareFrameRegions(cells,center,full,dx,dy,clip,[this](const PixelRect& r){refreshFrameDepth(r);},present,terrain);
}
void Renderer::refreshCellTerrainDepth(int identity,TerrainCellPoint point,std::int8_t level,
        PixelPoint screen,const PixelRect& clip,const FillStoreTrace& stores){
    if(identity<0||std::size_t(identity)>=assets_.map.cells.size())
        throw std::invalid_argument("Terrain depth Cell owner unbound");
    const auto& cell=assets_.map.cells.at(std::size_t(identity));
    if(cell.x!=point.x||cell.y!=point.y||std::int8_t(cell.z)!=level)
        throw std::invalid_argument("Terrain depth Cell association differs");
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=depth_.size()||
        colors_.size()!=depth_.size()||alpha_.size()!=depth_.size()||depth_.size()>UINT32_MAX/2)
        throw std::invalid_argument("Terrain depth planes not prepared");
    const auto image=assets_.tiles.find(0);
    if(image==assets_.tiles.end()||image->second.empty()||image->second.front().basePixels.empty()||!(image->second.front().flags&2))
        throw std::invalid_argument("Terrain depth first resident template unbound");
    const auto& light=mapLights_.at(std::size_t(identity));
    const auto brightness=std::bit_cast<std::int16_t>(std::uint16_t(light.terrain));
    (void)brightness; // Forwarded signed Cell10C; this profile's stores ignore shade/depth base.
    const auto& palettes=terrainPalettes(light.tint);
    if(palettes.empty()||terrainDepthReferences_==0)throw std::invalid_argument("Terrain retained converter association unbound");
    const std::uint32_t begin=0,end=std::uint32_t(depth_.size()*2),extent=end,buffer=0;
    const std::int32_t bpp=2;
    const auto surface=[&](int i){return SurfacePixelView{renderWidth_,i==0?terrainColorLock_:i==1?frameDepthLock_:terrainAlphaLock_,
        bpp,buffer,{},i==0?std::span<std::uint16_t>(colors_):i==1?std::span<std::uint16_t>(depth_):std::span<std::uint16_t>(alpha_),true};};
    FrameDepthView depth{frameDepthOffset_,begin,end,extent,renderWidth_,{{},depth_}},alpha{frameAlphaOffset_,begin,end,extent,renderWidth_,{{},alpha_}};
    TerrainDepthServices s;
    s.acquire41e3e0=[&]{retainTerrainDepthAlpha(terrainDepthReferences_);};
    s.release41e510=[&]{releaseTerrainDepthAlpha(terrainDepthReferences_);};
    s.bytes70=[&]{return bpp;};s.header9c=[&]{return !image->second.front().basePixels.empty();};
    s.pitch74=[&]{return surfacePixelPitch(surface(0));};s.lock5c=[&](int x,int y){return lockSurfacePixels(surface(0),x,y);};
    s.unlock60=[&]{unlockSurfacePixels(surface(0));};
    const auto address=[&](int i,PixelPoint p){FrameDepthServices s;
        s.lock5c=[&](int x,int y){return lockSurfacePixels(surface(i),x,y);};s.unlock60=[&]{unlockSurfacePixels(surface(i));};
        return framePlaneAddress(i==1?depth:alpha,p,s);};
    s.depth776340=[&](PixelPoint p){return address(1,p);};s.alpha411230=[&](PixelPoint p){return address(2,p);};
    drawTerrainDepth(depth,screen,clip,0,image->second.front().flags,true,s,stores);
}
void Renderer::modifyFramePlane(bool alpha,bool clear,PixelPoint delta,
        const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>& stores){
    auto& plane=alpha?alpha_:depth_;auto& lock=alpha?terrainAlphaLock_:frameDepthLock_;
    if(renderWidth_<=0||renderHeight_<=0||std::uint64_t(renderWidth_)*std::uint32_t(renderHeight_)!=plane.size()||plane.size()>UINT32_MAX/2)
        throw std::invalid_argument("Frame plane not prepared");
    const std::uint32_t begin=0,end=std::uint32_t(plane.size()*2),extent=end;const int bpp=2;
    FramePlaneView v{alpha?frameAlphaOffset_:frameDepthOffset_,begin,end,extent,
        alpha?frameAlphaBase_:frameDepthBase_,renderWidth_,renderHeight_,{{},plane}};
    const auto pixels=[&](auto p,auto n,auto value){if(stores)stores(alpha,p,n,value);};
    const auto fill=[&](FillRect r,std::uint32_t value){
        (void)fillSurfaceRectThrough({renderWidth_,renderHeight_,bpp,lock,{},begin,plane},r,value,pixels);
    };
    if(clear)clearFramePlane(v,alpha?127u:65535u,fill);
    else scrollFramePlane(v,delta.x,delta.y,alpha?127u:65535u,fill,pixels);
}
void Renderer::clearFramePlanes(const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>& stores){
    modifyFramePlane(false,true,{},stores);modifyFramePlane(true,true,{},stores);
}
void Renderer::scrollFramePlanes(PixelPoint delta,const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>& stores){
    modifyFramePlane(false,false,delta,stores);modifyFramePlane(true,false,delta,stores);
}
const PixelRect& Renderer::buildingBounds(Coord raw,BuildingRenderBoundsState& cache,
        const std::function<PixelRect()>& typeBounds)const{
    return buildingRenderBounds(cache,{[raw]{return buildingRenderCoordinates(raw);},
        [this]{return viewportOrigin();},[this](Coord p){return projectFrameCoordinates(p);},typeBounds,{}});
}
PixelPoint Renderer::projectFrameCoordinates(Coord p)const{
    (void)viewportOrigin(); // Refresh actual camera-derived origin/dimensions.
    PixelPoint out;(void)projectTacticalFrame(p,out,heightScale_,tacticalWidth_,tacticalHeight_,
        {[this]{return viewportOrigin();},{}});return out;
}
void Renderer::invalidateBuildings(PixelRect requested,const PixelPoint& screenOffset,const FrameInvalidationRegistry& objects){
    invalidateFrameBuildings(requested,screenOffset,objects,[this](PixelRect bounds,std::uint8_t flag){registerFrameDirtyRegion(bounds,flag);});
}
void Renderer::registerFrameDirtyRegion(PixelRect bounds,std::uint8_t flag){
    registerDirtyRegion(frameDirtyRegions_,{bounds,flag},[](DirtyRegionQueue& queue,int capacity){
        try{queue.slots.resize(std::size_t(capacity));return true;}
        catch(const std::bad_alloc&){return false;}
    });
}
Point Renderer::project(double x,double y,double z) const {
    const auto p=worldPixels(heightScale_,{int(std::llround(x*256)),int(std::llround(y*256)),int(std::llround(z*104))});
    const auto origin=viewportOrigin();return {(p.x-origin.x)*camera.zoom,(p.y-origin.y)*camera.zoom};
}
Position Renderer::unproject(double x,double y,double z) const {
    const auto origin=viewportOrigin();const double a=(x/camera.zoom+origin.x)/30;
    const double b=(y/camera.zoom+origin.y+heightPixels(heightScale_,int(std::llround(z*104))))/15;
    return {(a+b)/2,(b-a)/2}; // input/camera adapter, original tactical inverse not yet recovered
}
void Renderer::center(Coord location) {
    const auto p=worldPixels(heightScale_,location);camera.x=p.x;camera.y=p.y;
}
void Renderer::center(const Simulation& sim){center(sim.coordinates());}
bool Renderer::centerScenery(std::size_t index) {
    if(assets_.scenery.empty())return false;
    const auto& tree=assets_.scenery[index%assets_.scenery.size()];const auto x=tree.x,y=tree.y;
    const auto p=worldPixels(heightScale_,{x*256+128,y*256+128,assets_.cell(x,y)->z*104});
    camera.x=p.x;camera.y=p.y;return true;
}
bool Renderer::centerProp(std::size_t index) {
    std::vector<std::size_t> props;
    for(std::size_t i=0;i<assets_.scenery.size();++i)if(!assets_.scenery[i].type.starts_with("tree"))props.push_back(i);
    return !props.empty()&&centerScenery(props[index%props.size()]);
}
void Renderer::terrain() {
    renderWidth_=int(std::ceil(width/camera.zoom));renderHeight_=int(std::ceil(height/camera.zoom));
    if(renderWidth_<1||renderHeight_<1||renderWidth_>4096||renderHeight_>4096)throw std::runtime_error("Invalid logical viewport");
    const auto count=std::size_t(renderWidth_)*renderHeight_;
    // Original alpha-buffer constructor fills 127. Keeping every pixel visible
    // is a host visibility policy; map brightness belongs to each blit input.
    ground_.assign(count,0x10c3);groundDepth_.assign(count,65535);groundAlpha_.assign(count,VisibleAlpha);vehicleCoverage_.resize(count);
    const auto origin=viewportOrigin();
    std::vector<const MapCell*> order;order.reserve(assets_.map.cells.size());for(const auto& c:assets_.map.cells)order.push_back(&c);
    std::stable_sort(order.begin(),order.end(),[](auto a,auto b){return a->x+a->y<b->x+b->y;});
    for(const auto* c:order) {
        const auto& tile=assets_.tile(*c);const int left=(c->x-c->y)*30-30+tile.x-origin.x,top=(c->x+c->y)*15-15*c->z+tile.y-origin.y;
        const int base=terrainDepthBase((c->x+c->y)*15-15*c->z-origin.y,c->z);
        const auto& light=lightingAt(*c);const auto& rows=terrainPalettes(light.tint);const auto& palette=rows[alphaShadeRow(VisibleAlpha,light.terrain,int(rows.size()))];
        for(int y=std::max(0,top);y<std::min(renderHeight_,top+tile.height);++y)for(int x=std::max(0,left);x<std::min(renderWidth_,left+tile.width);++x) {
            const auto source=std::size_t(y-top)*tile.width+x-left,dest=std::size_t(y)*renderWidth_+x;
            if(tile.coverage[source]&1) {
                const auto index=tile.basePixels[source];
                terrainPixel(index,tile.baseDepth[source],base,palette[index],ground_[dest],groundDepth_[dest]);
            }
            if((tile.coverage[source]&2)&&tile.extraDepth[source]<32) {
                const auto index=tile.extraPixels[source];
                terrainPixel(index,tile.extraDepth[source],base,palette[index],ground_[dest],groundDepth_[dest]);
            }
        }
    }
    sceneryPixels=sceneryShadowPixels=propPixels=propShadowPixels=0;
    if(!assets_.scenery.empty()) {
        const auto& layer=assets_.sceneryLifecycle.objects.layers[2];
        auto drawActor=[&](int id,PixelPoint location,PixelRect clip){
            const auto& tree=assets_.scenery.at(std::size_t(id));
            const auto x=tree.x,y=tree.y;const auto& image=assets_.sceneryImages.at(tree.type);
            const auto& cell=*assets_.cell(x,y);const auto& light=lightingAt(cell);
            const auto inputs=staticTerrainDrawInputs(int(image.frames.size()),heightPixels(heightScale_,cell.z*104),std::int16_t(light.terrain));
            for(std::size_t i=0;i<inputs.size();++i) {
                const auto stats=blitTerrainFrame(image,inputs[i],location,clip,
                    terrainPalettes(light.tint),renderWidth_,renderHeight_,ground_,groundDepth_,groundAlpha_);
                (i?sceneryShadowPixels:sceneryPixels)+=stats.visible;
                if(!tree.type.starts_with("tree"))(i?propShadowPixels:propPixels)+=stats.visible;
            }
        };
        const PixelRect viewport{0,0,renderWidth_,renderHeight_};
        if(assets_.engineDataSource==PatchedEngineSha){
            StaticTerrainTraversalServices traversal;
            // Healthy static construction/whole-viewport invalidation remain
            // host policy. Only this hash has an executed static-scan profile.
            traversal.isTerrain=[](int){return true;};traversal.isDead=[](int){return false;};
            traversal.isAnimated=[](int){return false;};traversal.isCrumbling=[](int){return false;};
            traversal.renderBounds=[&](int id){
                const auto& life=assets_.sceneryLifecycle.actors.at(id);
                const auto& image=assets_.sceneryImages.at(assets_.scenery.at(std::size_t(id)).type);
                return terrainRenderBounds(&image,{life.screenX,life.screenY},origin);
            };
            traversal.clearRedraw=[&](int id){sceneryDrawStates_.at(id).needsRedraw=0;};
            traversal.drawIfVisible=[&](int id,PixelRect& clip,std::uint8_t force){
                TerrainVisibilityServices services;
                services.renderBounds=[&]{return traversal.renderBounds(id);};
                services.coordinates=[&]{return assets_.sceneryLifecycle.occupation.members.at(id).position;};
                services.project=[&](Coord p){const auto screen=worldPixels(heightScale_,p);return PixelPoint{screen.x-origin.x,screen.y-origin.y};};
                services.draw=[&](PixelPoint at,PixelRect bounds){drawActor(id,at,bounds);};
                drawTerrainIfVisible(sceneryDrawStates_.at(id),clip,viewport,{0,true,force},services);
            };
            // Native cache invalidation still requests a full viewport. The
            // recovered caller selects/forwards the actual static scan request.
            requestStaticTerrainRedraw({}, {},origin,viewport,{}, {},1,heightScale_,
                [&](std::uint8_t force,const PixelRect& dirty,const PixelRect& clip){
                    drawStaticTerrainRegion(std::span(layer.slots.data(),std::size_t(layer.count)),force,dirty,clip,viewport,traversal);
                });
        }else{
            // Retained disc profile keeps its historical forward rebuild;
            // patched-only traversal evidence is never relabeled as disc proof.
            for(int slot=0;slot<layer.count;++slot){
                const int id=layer.slots.at(std::size_t(slot));const auto& life=assets_.sceneryLifecycle.actors.at(id);
                drawActor(id,{life.screenX-origin.x,life.screenY-origin.y},viewport);
            }
        }
    }
    previous_=camera;valid_=true;
}
const RasterFrame& Renderer::prepareVehiclePart(const VehiclePart& model,VoxelCache& cache,std::int32_t key,const Matrix& pose,bool useCache) {
    if(model.voxels.sections.size()!=1)throw std::runtime_error("Multi-section voxel composition requires additional recovery");
    const auto result=cache.draw({key,true,assets_.disableVoxelCache||!useCache,true},[&]{
        const auto& section=model.voxels.sections.front();
        const auto shades=voxelSectionShades(assets_.rasterData,assets_.renderData,section.normalType,pose);
        const auto matrix=voxelMultiply(voxelIdentity(),voxelMultiply(pose,model.animation.at(0,0)));
        return rasterVoxel(assets_.rasterData,section,matrix,shades,assets_.voxelPalette);
    });
    if(!result.frame)throw std::runtime_error("Missing loaded unit raster frame");
    if(result.built)++voxelBuilds;else ++voxelHits;
    return *result.frame;
}
void Renderer::vehicle(const Simulation& sim,PixelPoint at,PixelRect clip) {
    const auto box=staging_.dirty;
    const PixelPoint destination{at.x+box.x-128,at.y+box.y-128};
    // Ordinary healthy profile: coordinate-derived cell ambient plus rules extra;
    // final colors select the house converter independently of local source tint.
    // Bridges, cell/status flags and full actor draw dispatch remain outside it.
    const auto locationCell=unitLightCell(sim.drive.position.x,sim.drive.position.y);
    const auto* cell=assets_.cell(locationCell.x,locationCell.y);
    if(!cell)throw std::runtime_error("Unit outside prepared lighting cells");
    const auto stats=blitUnit(staging_.pixels,256,256,box,destination,clip,flatUnitDepthAdjust(heightScale_,sim.elevation*104),unitBrightnessAt(*cell),
             unitConverter().shades,renderWidth_,renderHeight_,colors_,depth_,alpha_,&vehicleCoverage_);
    vehiclePixels+=stats.visible;terrainRejections+=stats.rejected;

}
void Renderer::vehicleShadow(const Matrix& model,const Simulation& sim,bool useCache,PixelPoint at,PixelRect clip) {
    const auto heading=sim.drive.body.current(sim.tick);
    const auto key=flatUnitShadowKey(bodyVoxelKey(voxelHeading(heading),0),heading);
    // Healthy ordinary Drive: ground-relative height and Shadow_Point are zero.
    // Shared pool, status/ramp/tilt/timer invalidation and lifecycle remain open.
    const auto result=shadowCache_.draw({key,false,assets_.noShadow,false,true,assets_.disableShadowCache||!useCache,true},[&]{
        const auto pose=voxelMultiply(model,assets_.body.animation.at(0,0));
        return rasterVoxelShadow(assets_.body.voxels.sections[0],pose,voxelCameraMatrix(assets_.rasterData),
                        voxelShadowOffset(assets_.rasterData,assets_.renderData.lightAngle),{staging_.pixels,256,256,{0,0}});
    });
    if(!result.frame)return;
    if(result.built)++shadowBuilds;else ++shadowHits;
    const auto& shadow=*result.frame;
    const auto& b=shadow.rectangle;
    const auto placement=footShadowPlacement({at.x+b[0],at.y+b[1]},{0,0},true,1);
    const auto stats=blitShadow(shadow.pixels,256,256,{b[2],b[3],b[4],b[5]},*placement,
                       clip,flatUnitDepthAdjust(heightScale_,sim.elevation*104),renderWidth_,renderHeight_,colors_,depth_);
    shadowPixels=stats.visible;
}
void Renderer::drawVehicle(const Simulation& sim,PixelPoint at,PixelRect clip,bool shadows,bool useShadowCache,bool useVoxelCache) {
    const auto body=sim.drive.body.current(sim.tick),turret=sim.drive.turret.current(sim.tick);
    const auto cameraMatrix=voxelCameraMatrix(assets_.rasterData);
    const auto bodyPose=voxelMultiply(cameraMatrix,voxelBodyMatrix(assets_.rasterData,body));
    const auto turretPose=voxelMultiply(cameraMatrix,voxelTurretMatrix(assets_.rasterData,body,turret));
    const auto bodyKey=bodyVoxelKey(voxelHeading(body),0),turretKey=turretVoxelKey(bodyKey,turret,0);
    const auto& bodyFrame=prepareVehiclePart(assets_.body,body_,bodyKey,bodyPose,useVoxelCache);
    const auto& turretFrame=prepareVehiclePart(assets_.turret,turret_,turretKey,turretPose,useVoxelCache);
    const auto& barrelFrame=prepareVehiclePart(assets_.barrel,barrel_,turretKey,turretPose,useVoxelCache);
    staging_.clear();staging_.add(bodyFrame,stagingRemap_);
    if(barrelAfterTurret(turret)){staging_.add(turretFrame,stagingRemap_);staging_.add(barrelFrame,stagingRemap_);}
    else {staging_.add(barrelFrame,stagingRemap_);staging_.add(turretFrame,stagingRemap_);}
    vehicle(sim,at,clip);
    if(shadows)vehicleShadow(voxelBodyMatrix(assets_.rasterData,body),sim,useShadowCache,at,clip);
}
void Renderer::drawPatchedVehicle(const Simulation* sim,int tick,PixelPoint at,PixelRect clip,bool shadows,bool useShadowCache,bool useVoxelCache,
    OwnedUnitDrawScene* scene,const OwnedUnitDrawActor* owned) {
    ++unitCallerCalls;
    const auto* live=owned?&owned->state:sim->groundState();
    const auto& bodyFacing=owned?live->movement.body:sim->drive.body;
    const auto& turretFacing=owned?owned->turret:sim->drive.turret;
    auto& resource=owned?ownedActors_.at(owned->id).resource:unitResource_;
    auto& indexes=owned?ownedType_.lit.parts:unitWorld_.unit.indexes;
    auto& shadowIndex=owned?ownedType_.shadow:unitWorld_.shadow;
    const auto floor=[&](Coord p){return scene?scene->map.floor(p):terrainView_->floor(p);};
    const auto coordinate=[&](Coord p)->const MapCellInput&{
        const auto& cell=scene?scene->map.coordinate(p):terrainView_->coordinate(p);
        if(owned)lastUnitCellRamp=cell.slope;return cell;
    };
    const auto attribute=[&](MapInputPosition p)->const MapCellAttributes&{return scene?scene->map.cell(p):terrainView_->cell(p);};
    const auto relative=[&](Coord p){return scene?scene->map.relative(p):terrainView_->relative(p);};
    OrdinaryUnitDrawInputs actor;actor.actor=owned?owned->id:0;
    actor.coordinates=owned?live->movement.actor.position:sim->coordinates();actor.extraLight=extraUnitLight_;
    UnitVoxelDrawInputs input;
    input.bodyHeading=bodyFacing.current(tick);input.turretHeading=turretFacing.current(tick);
    // Recovered stock FireAngle=8 settles at 14336. Placement timing and actor
    // construction remain supplied; the prototype starts in the settled state.
    input.barrelHeading=14336;input.camera=voxelCameraMatrix(assets_.rasterData);
    // Diagnostic bypass supplies the separate global key gate as zero as well:
    // otherwise the original warm-matrix shortcut can precede a disabled child.
    // The original global gate's lifetime/selection is not recovered.
    input.keyGate=useVoxelCache?1:0;
    UnitCallerWorldServices services;auto& c=services.caller;
    c.loadShape=[]{return 0u;}; // Unused harvester/decoration resource service.
    c.layer=[]{return 0;};c.registerScreen=[&](int id,PixelPoint p){
        registerUnitScreen(unitRegistry_,id,p,viewportOrigin(),renderWidth_,renderHeight_);
    };
    c.groundHeight=[&](Coord){return owned?actor.coordinates.z:sim->elevation*104;};
    c.coordinateCell=[](Coord){return UnitDrawCell{};}; // Bridge/status flags are zero.
    c.lightCell=[&](UnitLightCell p){
        ++unitLightLookups;const auto* cell=assets_.cell(p.x,p.y);
        if(!cell)throw std::runtime_error("Unit outside prepared caller lighting cells");
        return UnitDrawCell{std::int16_t(lightingAt(*cell).ambient),0};
    };
    c.brightnessPredicate=[]{return std::uint8_t(0);};c.originalTypeVisible=[]{return std::uint8_t(1);};
    c.alternateType=[]{throw std::runtime_error("Alternate Unit type requires recovery");};
    c.footDecoration=[](PixelPoint,PixelRect){};c.timerDecoration=[]{}; // Native UI below.
    auto& w=services.world;auto& s=w.actor;
    s.originalTypeVisible=s.bodyPose=s.multipleTurretQuery=s.shadowPose=s.status=s.height=s.cell=[]{};
    s.finalBrightness=[](int b){return unitBrightnessEffect(b,0);};s.predicate=[]{return std::uint8_t(0);};
    s.part.flag204=s.part.flag205=s.part.house=s.part.predicateC0=[]{return std::uint8_t(0);};
    s.part.kind=[]{};s.part.selectBlitter=[](auto){};
    w.metadata=assets_.unitDrawMetadata;w.map.invalid={-32768,-32768};
    w.map.coordinates=[&]{return footDepthCoordinates(actor.coordinates.x,actor.coordinates.y);};
    w.map.cell=[&](UnitLightCell p)->const FootDepthCell*{
        const auto i=assets_.cellIndex.find({p.x,p.y});
        return i==assets_.cellIndex.end()?nullptr:&unitDepthCells_.at(i->second);
    };
    // Neutral flat map/type/contact construction is still a host boundary.
    // Do not infer tunnel/bridge/cliff fields from the native map representation.
    w.map.cellPredicate=[](const FootDepthCell&){return false;};w.baseDepth=[&]{return flatUnitDepthAdjust(heightScale_,owned?actor.coordinates.z:sim->elevation*104);};
    w.contact.firstContact=[]{return false;};w.contact.contactKind=[]{return 0;};w.contact.contactType1357=[]{return std::uint8_t(0);};
    // The recovered surface consumer tests only zero/nonzero. Empty contacts
    // remain supplied, independently of the real movement target's lifetime.
    w.actor494=owned?owned->surfaceTarget494():0;
    const auto contains=[](const VoxelSnapshotIndex& i,int key){const auto keys=i.keys();return std::find(keys.begin(),keys.end(),key)!=keys.end();};
    c.draw=[&](bool,PixelPoint,PixelRect,int b){
        lastUnitBrightness=b;
        const int body=bodyVoxelKey(input.keyGate?voxelHeading(input.bodyHeading):-1,0),turret=turretVoxelKey(body,input.turretHeading,0);
        for(std::size_t part=0;part<3;++part){
            const int key=part?turret:body;
            if(assets_.disableVoxelCache||!useVoxelCache||!contains(indexes[part],key))++voxelBuilds;else ++voxelHits;
        }
    };
    // Instrumentation observes immutable staging/planes on a scratch surface.
    // It neither supplies nor changes the actual recovered final-world draw.
    w.surface=[&](const UnitSurfaceRequest& r){
        lastUnitDepth=r.depth;lastUnitGradient=r.gradient;
        auto scratch=colors_;const auto& pixels=owned?ownedStage_.image.pixels:unitWorld_.unit.image.pixels;
        const auto stats=r.gradient==0?blitUnitTopGradient(pixels,256,256,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,
            unitConverter().shades,renderWidth_,renderHeight_,scratch,depth_,alpha_):
            blitUnit(pixels,256,256,r.source,{r.destination.x,r.destination.y},r.clip,r.depth,r.brightness,
            unitConverter().shades,renderWidth_,renderHeight_,scratch,depth_,alpha_);
        vehiclePixels+=stats.visible;terrainRejections+=stats.rejected;
    };
    std::vector<std::uint16_t> beforeShadow;
    s.shadow=[&](const UnitVoxelShadowRequest& r){
        beforeShadow=colors_;
        if(!shadows||assets_.noShadow)return;
        if(assets_.disableShadowCache||!useShadowCache||r.key==-1||!contains(shadowIndex,r.key))++shadowBuilds;else ++shadowHits;
    };
    if(terrainView_){
        if(!live)throw std::runtime_error("Prepared drawing requires live ground movement state");
        const auto& map=*assets_.preparedTerrain;
        lastUnitAbsoluteZ=actor.coordinates.z;lastUnitStoredRamp=live->ramps.current;
        // On the mutable owner, telemetry observes actual consumer queries.
        // It must not warm lazy floor/fallback state before the recovered draw.
        if(!owned){lastUnitRelativeHeight=relative(actor.coordinates);lastUnitCellRamp=coordinate(actor.coordinates).slope;}
        c.groundHeight=[&](Coord p){return floor(p);};
        c.coordinateCell=[&](Coord p){return UnitDrawCell{0,coordinate(p).flags};};
        // Preserve canonical prepared-record identity, including the fallback.
        std::map<const MapCellAttributes*,FootDepthCell> views;
        w.map.tileBase=map.theater.depthBases[15];w.map.invalid={-32768,-32768};
        w.map.cell=[&](UnitLightCell p)->const FootDepthCell*{const auto& cell=attribute({p.x,p.y});const auto& v=cell.input;
            auto& out=views[&cell];out={{v.position.x,v.position.y},v.flags,v.tile,v.land,v.tube,v.level};return &out;};
        w.map.cellPredicate=[](const FootDepthCell& cell){return footDepthCellPredicate(cell,0);};
        w.baseDepth=[&]{
            UnitBaseDepthInputs in;in.location=actor.coordinates;in.facing=bodyFacing;in.tick=tick;in.heightScale=heightScale_;
            UnitBaseDepthWorld binding;binding.tiles=map.tiles;binding.overlays=map.overlays;
            binding.cell=[&](MapInputPosition p)->const MapCellAttributes&{return attribute(p);};
            binding.dimensions=[&](int tile,int){if(tile<0||std::size_t(tile)>=map.tiles.size()||!map.tiles[std::size_t(tile)].image)
                throw std::runtime_error("Prepared drawing needs an available TMP dimension record");};
            return ordinaryUnitBaseDepth(in,binding).depth;
        };
        s.cell=[&]{(void)coordinate(actor.coordinates);};
        GroundUnitBodyServices body;
        body.pose=[&](std::int32_t* key){DriveBodyInputs in;in.ramp=live->ramps;in.tick=tick;
            // Rocking remains zero. Type extent inputs do not contribute at zero
            // rocking; dynamic rocking/physics and their association stay open.
            return driveBodyPose(assets_.rasterData,rampPoseData_,rampMatrices_,rampQuaternions_,in,
                [&]{return bodyFacing.current(tick);},key);};
        body.observePart=[&](UnitVoxelPart part,int key,const Matrix&){const auto index=std::size_t(part);
            if(assets_.disableVoxelCache||!useVoxelCache||key==-1||!contains(indexes[index],key))++voxelBuilds;else ++voxelHits;};
        GroundUnitShadowServices ground;
        ground.pose=[&](std::int32_t* key){DriveShadowInputs in;in.position=actor.coordinates;in.tick=tick;
            in.slopeStart=live->ramps.start;in.slopeRemaining=live->ramps.remaining;in.slopeDuration=live->ramps.duration;
            return driveShadowPose(assets_.rasterData,rampMatrices_,in,
                {[&](Coord p){return coordinate(p).slope;},[&]{return bodyFacing.current(tick);}},key);};
        ground.relativeHeight=[&]{const int height=relative(actor.coordinates);if(owned)lastUnitRelativeHeight=height;return height;};
        ground.point=[&]{return PixelPoint{0,heightPixels(heightScale_,ground.relativeHeight())};};
        c.draw=[&](bool voxel,PixelPoint point,PixelRect bounds,int brightness){
            if(!voxel)throw std::runtime_error("Prepared drawing requires ordinary voxel Unit");lastUnitBrightness=brightness;
            auto in=input;in.point=point;in.clip=bounds;in.brightness=brightness;
            if(owned)drawSharedPosedGroundUnitVoxelToWorld(assets_.rasterData,assets_.renderData,
                {&assets_.body.voxels,&assets_.turret.voxels,&assets_.barrel.voxels},
                {&assets_.body.animation,&assets_.turret.animation,&assets_.barrel.animation},assets_.voxelPalette,in,
                assets_.disableVoxelCache||!useVoxelCache,assets_.noShadow||!shadows,assets_.disableShadowCache||!useShadowCache,
                ownedStage_,ownedType_,ownedActors_.at(owned->id).stage,w,body,ground,stagingRemap_,
                {renderWidth_,renderHeight_,colors_,depth_,alpha_,unitConverter().shades});
            else drawPosedGroundUnitVoxelToWorld(assets_.rasterData,assets_.renderData,
                {&assets_.body.voxels,&assets_.turret.voxels,&assets_.barrel.voxels},
                {&assets_.body.animation,&assets_.turret.animation,&assets_.barrel.animation},assets_.voxelPalette,in,
                assets_.disableVoxelCache||!useVoxelCache,assets_.noShadow||!shadows,assets_.disableShadowCache||!useShadowCache,
                unitWorld_,w,body,ground,stagingRemap_,{renderWidth_,renderHeight_,colors_,depth_,alpha_,unitConverter().shades});
        };
        drawOrdinaryUnitCaller(resource,actor,at,clip,c);
    }else drawHealthyUnitCallerToWorld(assets_.rasterData,assets_.renderData,
        {&assets_.body.voxels,&assets_.turret.voxels,&assets_.barrel.voxels},
        {&assets_.body.animation,&assets_.turret.animation,&assets_.barrel.animation},assets_.voxelPalette,
        unitResource_,actor,at,clip,input,assets_.disableVoxelCache||!useVoxelCache,
        assets_.noShadow||!shadows,assets_.disableShadowCache||!useShadowCache,unitWorld_,services,stagingRemap_,
        {renderWidth_,renderHeight_,colors_,depth_,alpha_,unitConverter().shades});
    if(!beforeShadow.empty())for(std::size_t i=0;i<colors_.size();++i)shadowPixels+=colors_[i]!=beforeShadow[i];
    if(owned)ownedDraws.push_back({owned->id,actor.coordinates,input.bodyHeading,input.turretHeading,
        lastUnitDepth,lastUnitRelativeHeight,lastUnitStoredRamp,lastUnitCellRamp,w.actor494!=0});
}
void Renderer::drawDynamic(const Simulation* sim,int tick,bool shadows,bool useShadowCache,bool useVoxelCache,OwnedUnitDrawScene* scene) {
    const auto origin=viewportOrigin();
    const auto inputs=initialUnitDrawingInputs(0); // Supplied zero upper allocation bits.
    std::vector<TraversalActor> actors;
    actors.reserve(assets_.scenery.size()+(scene?scene->actors.size():1));
    for(std::size_t i=0;i<assets_.scenery.size();++i)
        actors.push_back({TraversalKind::Terrain,2,0,0,0,assets_.sceneryLifecycle.occupation.members.at(int(i)).position});
    const int firstUnit=int(actors.size());
    if(scene)for(const auto& actor:scene->actors)
        actors.push_back({TraversalKind::Unit,inputs.flags,0,0,0,actor.state.movement.actor.position});
    else actors.push_back({TraversalKind::Unit,inputs.flags,0,0,0,sim->coordinates()});
    const auto ownedActor=[&](int id)->const OwnedUnitDrawActor*{
        if(id<firstUnit||std::size_t(id)>=actors.size())throw std::runtime_error("Unexpected dynamic Unit identity");
        return scene?&scene->actors[std::size_t(id-firstUnit)]:nullptr;
    };
    const auto& registered=assets_.sceneryLifecycle.objects.layers[2];
    std::vector<int> ground(registered.slots.begin(),registered.slots.begin()+registered.count);
    // Host registration/order; original Unit layer maintenance remains open.
    for(int id=firstUnit;std::size_t(id)<actors.size();++id)ground.push_back(id);
    std::array<std::span<const int>,5> layers{};layers[2]=ground;
    PixelRect viewport{0,0,renderWidth_,renderHeight_};
    DynamicTraversalContext context;
    context.origin=origin;context.surfaceWidth=renderWidth_;context.surfaceHeight=renderHeight_;
    context.heightScale=heightScale_;context.force=1;
    // Every display starts from the host's complete static color/depth cache.
    // Force=1 is its redraw policy, not recovered original frame scheduling.
    DynamicTraversalServices services;
    services.type=[&](int id){return actors.at(id).kind;};
    services.inverse=[](TraversalVector p){
        return TraversalVector{float((double(p.x)/30+double(p.y)/15)*128),
                               float((double(p.y)/15-double(p.x)/30)*128),0};
    };
    services.coordinates=[&](int id){return actors.at(id).location;};
    services.footCoordinates=[&](int id){
        ++footQueries;const auto* actor=ownedActor(id);const auto location=actors.at(id).location;
        auto head=actor?actor->state.movement.head:sim->drive.head;
        if(head!=Coord{}&&!scene&&!sim->groundState())head.z+=location.z;
        (void)footSecondaryCoordinates(inputs.secondaryIndex,{},
            {[&]{return driveSecondaryCoordinates(location,head);},[&]{return location;}});
    };
    services.mapRejects=[](int,Coord){return false;}; // Scenario bit 0x1000 is clear.
    services.drawBehind=[](int,PixelPoint,PixelRect&){}; // Actual ordinary Unit type=1 exit.
    services.drawIfVisible=[&](int id,PixelRect& bounds,int force,int third){
        if(third!=0)throw std::runtime_error("Unexpected healthy dynamic drawing branch");
        const auto* actor=ownedActor(id);const auto location=actors.at(id).location;
        UnitVisibilityServices drawing;
        drawing.coordinates=[&]{return location;};
        drawing.project=[&](Coord p){const auto q=worldPixels(heightScale_,p);
            return std::pair{PixelPoint{q.x-origin.x,q.y-origin.y},true};}; // Host tactical visibility.
        drawing.draw=[&](PixelPoint at,PixelRect clip){++unitDrawCalls;
            drawPatchedVehicle(sim,tick,at,clip,shadows,useShadowCache,useVoxelCache,scene,actor);};
        auto& state=actor?ownedActors_.at(actor->id).visibility:unitDrawState_;
        drawOrdinaryUnitIfVisible(state,bounds,viewport,{0,true,std::uint8_t(force)},inputs.specialState,drawing);
    };
    services.drawExtras=[&](int,PixelPoint,PixelRect&){++extrasCalls;}; // Native selection UI follows below.
    drawDynamicLayers(actors,layers,viewport,context,services,[&](int,std::uint8_t value){dynamicClears+=value==0;});
    unitVisible=actors.at(firstUnit).visible!=0;
}
void Renderer::drawOwned(const Simulation& sim,OwnedUnitDrawScene& scene,bool terrainOcclusion,bool shadows,bool shadowCache,bool voxelCache){
    drawOwned(OwnedUnitDrawFrame{sim.tick},scene,terrainOcclusion,shadows,shadowCache,voxelCache);
}
void Renderer::drawOwned(OwnedUnitDrawFrame frame,OwnedUnitDrawScene& scene,bool terrainOcclusion,bool shadows,bool shadowCache,bool voxelCache){
    if(!terrainView_||assets_.engineDataSource!=PatchedEngineSha||scene.actors.size()!=2||
       scene.actors[0].id!=0||scene.actors[1].id!=1||&scene.actors[0].state==&scene.actors[1].state||
       &scene.map.actorState(0)!=&scene.actors[0].state||&scene.map.actorState(1)!=&scene.actors[1].state||
       scene.selected< -1||scene.selected>1)
        throw std::invalid_argument("Owned drawing requires distinct actors on prepared base terrain");
    if(ownedStage_.pool.bytes.empty())ownedStage_.pool.bytes.resize(0x80000);
    for(const auto& actor:scene.actors)ownedActors_.try_emplace(actor.id);
    drawScene(nullptr,frame.tick,terrainOcclusion,shadows,shadowCache,voxelCache,&scene);
}
void Renderer::draw(const Simulation& sim,bool terrainOcclusion,bool shadows,bool shadowCache,bool voxelCache){
    drawScene(&sim,sim.tick,terrainOcclusion,shadows,shadowCache,voxelCache,nullptr);
}
void Renderer::drawScene(const Simulation* sim,int tick,bool terrainOcclusion,bool shadows,bool useShadowCache,bool useVoxelCache,OwnedUnitDrawScene* scene) {
    if(!valid_||!(camera==previous_)) terrain();colors_=ground_;depth_=groundDepth_;alpha_=groundAlpha_;terrainRejections=0;
    vehiclePixels=shadowPixels=0;std::fill(vehicleCoverage_.begin(),vehicleCoverage_.end(),0);
    dynamicClears=footQueries=unitDrawCalls=extrasCalls=0;unitVisible=false;ownedDraws.clear();
    unitCallerCalls=unitLightLookups=0;lastUnitBrightness=0;unitRegistry_.count=0;
    if(!terrainOcclusion)std::fill(depth_.begin(),depth_.end(),65535); // diagnostic comparison only
    auto at=scene?Point{}:project(sim->position.x,sim->position.y,sim->drawElevation());
    if(scene&&scene->selected>=0){const auto p=scene->actors[std::size_t(scene->selected)].state.movement.actor.position;at=project(p.x/256.0,p.y/256.0,p.z/104.0);}
    if(assets_.engineDataSource==PatchedEngineSha)drawDynamic(sim,tick,shadows,useShadowCache,useVoxelCache,scene);
    else{
        // Retain the historical disc integration; patched caller proof is separate.
        const auto p=worldPixels(heightScale_,{sim->drive.position.x,sim->drive.position.y,sim->elevation*104});
        const auto origin=viewportOrigin();
        drawVehicle(*sim,{p.x-origin.x,p.y-origin.y},{0,0,renderWidth_,renderHeight_},shadows,useShadowCache,useVoxelCache);
    }
    presentColors();
    const auto target=scene?(scene->selected>=0?scene->actors[std::size_t(scene->selected)].state.destination:Coord{}):
        (sim->selected&&sim->drive.hasDestination?sim->drive.destination:Coord{});
    if(target!=Coord{}) {
        // Temporary command marker; this is not recovered original UI.
        const auto goal=project(target.x/256.0,target.y/256.0,scene?target.z/104.0:sim->elevation);
        for(int i=-7;i<=7;++i) {
            auto put=[&](int x,int y){if(x>=0&&y>=0&&x<width&&y<height)pixels[std::size_t(y)*width+x]=0xfff7dc70;};
            put(int(goal.x)+i,int(goal.y));put(int(goal.x),int(goal.y)+i);
        }
    }
    if(scene?scene->selected>=0:sim->selected) {
        const int r=int(31*camera.zoom),h=int(21*camera.zoom);
        for(int i=0;i<11;++i) for(int sx:{-1,1}) for(int sy:{-1,1}) {
            auto put=[&](int x,int y){if(x>=0&&y>=0&&x<width&&y<height) pixels[std::size_t(y)*width+x]=0xff69f07f;};
            put(int(at.x)+sx*(r-i),int(at.y-8*camera.zoom)+sy*h);put(int(at.x)+sx*r,int(at.y-8*camera.zoom)+sy*(h-i));
        }
    }
}
void Renderer::presentColors() {
    for(int y=0;y<height;++y)for(int x=0;x<width;++x) {
        const int sx=std::min(renderWidth_-1,int(x/camera.zoom)),sy=std::min(renderHeight_-1,int(y/camera.zoom));
        pixels[std::size_t(y)*width+x]=expand565(colors_[std::size_t(sy)*renderWidth_+sx]);
    }
}
std::shared_ptr<const ShpImage> Renderer::prepareBuildingDepthImage(){
    buildingDepthImage_.reset();
    auto image=std::make_shared<const ShpImage>(loadBuildingDepthImage(assets_.store,buildingDepthState_));
    buildingDepthImage_=std::move(image);return buildingDepthImage_;
}
SpriteConverterSelectionServices Renderer::spriteConverterSelectionServices()const{
    SpriteConverterSelectionServices s;
    s.globalBackingAB6EFC=[this]()->const void*{return &assets_.playerColors;};
    s.schemeAtOffset=[this](const void* backing,std::uint32_t offset)->const void*{
        const auto index=offset/4;
        if(offset%4||backing!=&assets_.playerColors||index>=assets_.playerColors.size())
            throw std::invalid_argument("Sprite scheme outside supplied renderer backing");
        auto it=assets_.playerColors.begin();std::advance(it,index);return &*it;
    };
    s.converter30c=[this](const void* scheme)->const void*{
        std::size_t index=0;for(const auto& entry:assets_.playerColors){
            if(scheme==&entry)return &houseConverters_.at(index);++index;
        }
        throw std::invalid_argument("Foreign renderer sprite scheme");
    };
    return s;
}
BlitStats Renderer::drawBuildingSpritePixels(const ShpImage& image,const TechnoSpriteBlit& b){
    if(b.image!=&image||b.surface!=this)
        throw std::invalid_argument("Building sprite image/surface/converter association unsupported");
    if(b.zero||bool(b.tail[0])!=bool(b.auxiliaryImage)||
       (b.auxiliaryImage&&b.auxiliaryImage!=buildingDepthImage_.get()))
        throw std::invalid_argument("Building sprite optional-depth profile unsupported");
    auto selected=std::find_if(houseConverters_.begin(),houseConverters_.end(),[&](const auto& c){return b.converter==&c;});
    if(selected==houseConverters_.end())throw std::invalid_argument("Building sprite foreign renderer converter");
    auto& converter=*selected;
    const auto stats=blitConvertedSpriteFrame({converter.field17c,converter.shades,{}},&image,
        {b.frame,b.flags,b.zAdjust,b.gradient,b.brightness},b.point,b.clip,
        renderWidth_,renderHeight_,colors_,depth_,alpha_,
        {b.auxiliaryImage?buildingDepthImage_.get():nullptr,b.tail[1],{b.tail[2],b.tail[3]}});
    presentColors();return stats;
}
void Renderer::drawMap() {
    if(!valid_||!(camera==previous_))terrain();
    colors_=ground_;depth_=groundDepth_;alpha_=groundAlpha_;presentColors();
}
int Renderer::hitOwnedActor(const OwnedUnitDrawScene& scene,double x,double y)const{
    double distance=1e30;int selected=-1;
    for(const auto& actor:scene.actors){const auto p=actor.state.movement.actor.position;
        const auto q=project(p.x/256.0,p.y/256.0,p.z/104.0);
        const double dx=std::abs(x-q.x),dy=std::abs(y-(q.y-8*camera.zoom));
        if(dx<36*camera.zoom&&dy<25*camera.zoom&&dx+2*dy<distance){distance=dx+2*dy;selected=actor.id;}}
    return selected;
}
bool Renderer::hitTank(const Simulation& sim,double x,double y) const {auto p=project(sim.position.x,sim.position.y,sim.drawElevation());return std::abs(x-p.x)<36*camera.zoom&&std::abs(y-(p.y-8*camera.zoom))<25*camera.zoom;}
void Renderer::writePpm(const std::filesystem::path& path) const {
    std::ofstream f(path,std::ios::binary);if(!f) throw std::runtime_error("Cannot write preview");f<<"P6\n"<<width<<" "<<height<<"\n255\n";
    for(auto p:pixels) {const char b[3]={char(p>>16),char(p>>8),char(p)};f.write(b,3);}if(!f) throw std::runtime_error("Preview write failed");
}
}
