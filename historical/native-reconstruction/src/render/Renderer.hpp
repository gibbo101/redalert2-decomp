// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SpriteConverterSelection.hpp"
#include "assets/BuildingDepthImage.hpp"
#include "assets/GameAssets.hpp"
#include "sim/Simulation.hpp"
#include "render/Lighting.hpp"
#include "render/MapLighting.hpp"
#include "render/StaticLight.hpp"
#include "render/UnitLighting.hpp"
#include "render/VoxelRaster.hpp"
#include "render/Composition.hpp"
#include "render/PlayerColor.hpp"
#include "render/VoxelShadow.hpp"
#include "render/UnitStaging.hpp"
#include "render/ShadowCache.hpp"
#include "render/VoxelCache.hpp"
#include "render/Scenery.hpp"
#include "render/TechnoSpriteDraw.hpp"
#include "render/StaticTerrainTraversal.hpp"
#include "render/DynamicTraversal.hpp"
#include "render/TacticalViewport.hpp"
#include "render/CellRedraw.hpp"
#include "render/BuildingFrameRedraw.hpp"
#include "render/BuildingRedrawRequests.hpp"
#include "render/BuildingRenderBounds.hpp"
#include "render/FrameInvalidation.hpp"
#include "render/Redraw.hpp"
#include "render/UnitVisibility.hpp"
#include "render/UnitCallerWorld.hpp"
#include "render/GroundUnitVoxelWorld.hpp"
#include "render/DriveBodyPose.hpp"
#include "render/OwnedUnitDrawScene.hpp"
#include "render/OwnedUnitDrawFrame.hpp"
#include "render/SharedGroundUnitVoxelWorld.hpp"
#include "render/CellVisibilityDraw.hpp"
#include "render/RectangularVisibility.hpp"
#include "render/AlphaAnimation.hpp"
#include <array>
namespace ra2 {
struct Point { double x=0,y=0; };
struct Camera {
    double x=0,y=0,zoom=1.5;
    bool operator==(const Camera&) const = default;
};
struct AlphaAnimationLifecycleServices;
class Renderer {
    const GameAssets& assets_;
    std::vector<std::uint16_t> ground_,groundDepth_,groundAlpha_,colors_,depth_,alpha_;
    Bytes vehicleCoverage_;
    std::map<std::array<int,3>,std::vector<Palette16>> terrainPalettes_;
    std::vector<UnitLightConverter> houseConverters_;
    std::size_t houseScheme_=0;
    BuildingDepthImageState buildingDepthState_;
    std::shared_ptr<const ShpImage> buildingDepthImage_; // One explicit shared depth-image owner.
    AlphaCombinationTable alphaCombination_;
    VisibilityRasterCache visibilityRasterCache_;
    std::map<std::string,Data> visibilityRasterImages_;
    int extraUnitLight_=0;
    MapLightSettings lightSettings_;
    std::vector<CellLight> mapLights_;
    std::optional<LightSource> staticLight_;
    int detail_=2;
    std::size_t lightUpdates_=0;
    void installStaticLight(int x,int y);
    const std::vector<Palette16>& terrainPalettes(std::array<int,3> tint);
    Camera previous_{};
    bool valid_=false;
    // Explicit unscheduled frame owner. Host growth/startup supplied; retain
    // entries until a complete original frame consumer is bound.
    DirtyRegionQueue frameDirtyRegions_{{},0,10,true};
    mutable TacticalViewportState tacticalViewport_;
    mutable int tacticalWidth_=-1,tacticalHeight_=-1;
    std::map<int,TerrainMarkState> sceneryDrawStates_;
    TerrainMarkState unitDrawState_{1,1,0}; // Healthy one-actor host lifetime.
    VoxelCache body_,turret_,barrel_;
    UnitStaging staging_;
    IndexRemap stagingRemap_{};
    ShadowCache shadowCache_;
    UnitVoxelShadowWorldState unitWorld_;
    SharedUnitVoxelStage ownedStage_;
    UnitVoxelWorldTypeIndexes ownedType_;
    struct OwnedDrawState {
        UnitDrawResource resource;
        TerrainMarkState visibility{1,1,0};
        UnitVoxelActorStage stage;
    };
    std::map<int,OwnedDrawState> ownedActors_;
    UnitDrawResource unitResource_;
    UnitScreenRegistry unitRegistry_;
    std::vector<FootDepthCell> unitDepthCells_; // Supplied neutral flat fields.
    std::unique_ptr<TerrainMapView> terrainView_;
    RampPoseData rampPoseData_;
    std::array<Matrix,21> rampMatrices_{};
    std::array<RampQuaternion,21> rampQuaternions_{};
    std::string playerColor_;
    void terrain();
    void presentColors();
    const RasterFrame& prepareVehiclePart(const VehiclePart& model,VoxelCache& cache,std::int32_t key,const Matrix& pose,bool useCache);
    void vehicle(const Simulation& sim,PixelPoint at,PixelRect clip);
    void vehicleShadow(const Matrix& model,const Simulation& sim,bool useCache,PixelPoint at,PixelRect clip);
    void drawVehicle(const Simulation&,PixelPoint,PixelRect,bool shadows,bool shadowCache,bool voxelCache);
    void drawPatchedVehicle(const Simulation*,int tick,PixelPoint,PixelRect,bool shadows,bool shadowCache,bool voxelCache,
        OwnedUnitDrawScene* scene=nullptr,const OwnedUnitDrawActor* actor=nullptr);
    void drawDynamic(const Simulation*,int tick,bool shadows,bool shadowCache,bool voxelCache,OwnedUnitDrawScene* scene=nullptr);
    void drawScene(const Simulation*,int tick,bool,bool,bool,bool,OwnedUnitDrawScene*);
    double heightScale_=0;
    int renderWidth_=0,renderHeight_=0;
    std::int32_t frameDepthLock_=0; // Supplied stock surface lock owner for the existing depth plane.
    std::int32_t terrainColorLock_=0,terrainAlphaLock_=0,terrainDepthReferences_=1;
    std::uint32_t frameDepthOffset_=0,frameAlphaOffset_=0;
    std::int32_t frameDepthBase_=32768,frameAlphaBase_=32768;
    void modifyFramePlane(bool alpha,bool clear,PixelPoint delta,
        const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>&);
    PixelPoint viewportOrigin() const;
public:
    CellRedrawView cellRedrawView()const;
    // Explicit frame dependency query; not a scheduled frame/reset operation.
    bool buildingRedrawPending(PixelRect,const BuildingFrameRegistry&)const;
    // Explicit6A4100 producer on the existing Cell/region owners. The scan
    // callback composes the existing Building registry; no queue clearing.
    void requestBuildingDraws(const CellRedrawQueue&,const std::function<TerrainCellPoint(int)>&,
        const PixelRect& first,const PixelRect& second,std::int32_t full,const StaticRedrawScan&)const;
    // Explicit6A33F0 on the same mutable regions; depth/terrain children remain
    // named services until recovered. This never clears the Cell queue.
    void prepareFrameRegions(const CellRedrawQueue&,const std::function<Coord(int)>&,
        std::int32_t full,std::int32_t dx,std::int32_t dy,const PixelRect& clip,
        const std::function<void(const PixelRect&)>& depth,
        const std::function<bool()>& terrainPresent,
        const std::function<void(int,PixelPoint,const PixelRect&)>& terrain);
    // Same parent with recovered7761C0 bound to this renderer's depth plane.
    void prepareFrameRegions(const CellRedrawQueue&,const std::function<Coord(int)>&,
        std::int32_t full,std::int32_t dx,std::int32_t dy,const PixelRect& clip,
        const std::function<bool()>& terrainPresent,
        const std::function<void(int,PixelPoint,const PixelRect&)>& terrain);
    void refreshFrameDepth(PixelRect,const FillStoreTrace& stores={});
    void refreshFrameAlpha(PixelRect,const FillStoreTrace& stores={});
    // Explicit475520 child effects on the existing alpha plane. Scheduling,
    // asset-loader internals and startup associations remain separate.
    void drawVisibilityMask(bool fog,const PixelPoint&,const PixelRect&,std::int32_t frame,
        const std::function<std::uint32_t()>& scenarioFlags,const FillStoreTrace& stores={});
    void drawVisibilityRectangle(const PixelRect&,RectangularVisibilityServices);
    // Explicit startup/drawing seams; registry, Type/cache associations and tile
    // mask are required borrowed inputs. No empty-registry startup substitution.
    void initializeAlphaAnimationTable(){initializeAlphaCombination(alphaCombination_);}
    AlphaAnimationRecord* constructAlphaAnimation(AlphaAnimationRecord&,const void* associated,
        std::int32_t x,std::int32_t y,bool defaultConstructor,const AlphaAnimationLifecycleServices&);
    void cleanupAlphaAnimations(const AlphaAnimationLifecycleServices&);
    void drawAlphaAnimations(bool pointPass,const PixelPoint&,const PixelRect&,AlphaAnimationServices,const FillStoreTrace& stores={});
    // Explicit6A3EF0; alpha uses the retained plane. Other entered draw children
    // are required services until recovered; no frame/sight/arrival scheduling.
    void requestTerrainDraws(const CellRedrawQueue&,const std::function<Coord(int)>& center,
        const PixelRect& first,const PixelRect& second,const PixelRect& clip,std::int32_t full,
        const std::function<bool()>& terrainPresent,
        const std::function<void(int,PixelPoint,const PixelRect&)>& terrain,
        const std::function<void(PixelPoint,const PixelRect&)>& animation,
        const std::function<void(const PixelRect&)>& rectangle,const FillStoreTrace& stores={});
    // Explicit stationary-full and scrolling children of6A45A0; no dispatcher,
    // surface swap, queue clearing or runtime camera-scroll scheduling.
    void clearFramePlanes(const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>& stores={});
    void scrollFramePlanes(PixelPoint delta,const std::function<void(bool,std::uint32_t,unsigned,std::uint32_t)>& stores={});
    std::uint32_t frameDepthOffset()const{return frameDepthOffset_;}
    std::uint32_t frameAlphaOffset()const{return frameAlphaOffset_;}
    std::int32_t frameDepthBase()const{return frameDepthBase_;}
    std::int32_t frameAlphaBase()const{return frameAlphaBase_;}
    // Explicit4754B0 fixed depth-only profile on the existing raster/Cell light
    // owners. First template/converter/retained cache association supplied.
    void refreshCellTerrainDepth(int identity,TerrainCellPoint,std::int8_t level,
        PixelPoint,const PixelRect&,const FillStoreTrace& stores={});
    std::int32_t terrainDepthReferences()const{return terrainDepthReferences_;}
    std::int32_t terrainColorLock()const{return terrainColorLock_;}
    std::int32_t terrainAlphaLock()const{return terrainAlphaLock_;}
    std::span<const std::uint16_t> frameColorPlane()const{return colors_;}
    std::span<const std::uint16_t> frameAlphaPlane()const{return alpha_;}
    std::span<const std::uint16_t> frameDepthPlane()const{return depth_;}
    std::int32_t frameDepthLockLevel()const{return frameDepthLock_;}
    std::size_t frameDepthRefreshCalls=0; // Native inspection telemetry, not original scheduling.
    // Recovered6A29D0 output, including its false-result output coordinates.
    PixelPoint projectFrameCoordinates(Coord)const;
    const PixelRect& buildingBounds(Coord raw,BuildingRenderBoundsState&,
        const std::function<PixelRect()>& typeBounds)const;
    void invalidateBuildings(PixelRect, const PixelPoint& screenOffset,const FrameInvalidationRegistry&);
    // Explicit recovered6A3020 on this same owner; invocation/startup supplied.
    void registerFrameDirtyRegion(PixelRect,std::uint8_t flag);
    const DirtyRegionQueue& frameDirtyRegions()const{return frameDirtyRegions_;}
    const TacticalViewportState& tacticalViewport()const{(void)viewportOrigin();return tacticalViewport_;}
    int width,height;
    Camera camera;
    std::vector<std::uint32_t> pixels;
    std::size_t terrainRejections=0,vehiclePixels=0;
    std::size_t shadowPixels=0;
    std::size_t sceneryPixels=0,sceneryShadowPixels=0; // Cached static viewport layer.
    std::size_t propPixels=0,propShadowPixels=0; // Subset, for native inspection checks.
    std::size_t shadowBuilds=0,shadowHits=0;
    std::size_t voxelBuilds=0,voxelHits=0;
    // Per-display integration telemetry, not original actor ownership/scheduling.
    std::size_t dynamicClears=0,footQueries=0,unitDrawCalls=0,extrasCalls=0;
    std::size_t unitCallerCalls=0,unitLightLookups=0;
    int lastUnitBrightness=0;
    int lastUnitDepth=0,lastUnitGradient=0;
    int lastUnitAbsoluteZ=0,lastUnitRelativeHeight=0,lastUnitStoredRamp=0,lastUnitCellRamp=0;
    bool unitVisible=false;
    struct OwnedActorTelemetry {
        int id;Coord location;std::uint16_t body,turret;
        int depth,relativeHeight,storedRamp,cellRamp;
        bool target494;
    };
    std::vector<OwnedActorTelemetry> ownedDraws;
    Renderer(const GameAssets& assets,int width,int height,const std::string& playerColor="DarkRed",int detail=2);
    void addLightDemo(int x,int y); // explicit host placement of stock invisible light
    std::size_t setLightActive(bool active);
    bool hasLight() const {return staticLight_.has_value();}
    bool lightActive() const {return staticLight_&&staticLight_->active;}
    std::size_t lightUpdates() const {return lightUpdates_;}
    void setPlayerColor(const std::string&);
    const std::string& playerColor() const {return playerColor_;}
    // Existing CellLight::ambient is the signed Cell10A input, not terrain height.
    // Registry-to-light index association is checked; fallback is not fabricated.
    std::int16_t buildingAmbient(int cellIdentity,TerrainCellPoint storedPoint)const;
    const CellLight& lightingAt(const MapCell&) const;
    int unitBrightnessAt(const MapCell&) const;
    // Supplied asset scheme -> existing converter association, no new palette cache.
    SpriteConverterSelectionServices spriteConverterSelectionServices()const;
    // Explicit preparation only; no constructor or SDL-frame scheduling.
    std::shared_ptr<const ShpImage> prepareBuildingDepthImage();
    const ShpImage* buildingDepthImage()const{return buildingDepthImage_.get();}
    const UnitLightConverter& unitConverter() const {return houseUnitConverter(houseConverters_,houseScheme_);}
    Point project(double x,double y,double z=0) const;
    Position unproject(double x,double y,double z) const;
    void center(const Simulation& sim);
    void center(Coord);
    bool centerScenery(std::size_t index); // Host camera inspection of recorded scenery.
    bool centerProp(std::size_t index); // Cycle the ordinary non-tree props only.
    void draw(const Simulation& sim,bool terrainOcclusion=true,bool shadows=true,bool useShadowCache=true,bool useVoxelCache=true);
    void drawMap(); // Terrain/scenery inspection, without a dummy actor/Simulation.
    // Explicit unscheduled ordinary SHP pixels on this renderer's current planes.
    // Supplied converter/surface association; optional depth borrows this renderer owner.
    BlitStats drawBuildingSpritePixels(const ShpImage&,const TechnoSpriteBlit&);
    void drawOwned(const Simulation&,OwnedUnitDrawScene&,bool terrainOcclusion=true,bool shadows=true,bool useShadowCache=true,bool useVoxelCache=true);
    void drawOwned(OwnedUnitDrawFrame,OwnedUnitDrawScene&,bool terrainOcclusion=true,bool shadows=true,bool useShadowCache=true,bool useVoxelCache=true);
    // Nearest projected actor bounds are a temporary host picking policy.
    int hitOwnedActor(const OwnedUnitDrawScene&,double x,double y)const;
    std::span<const UnitScreenEntry> registeredUnits()const{return {unitRegistry_.entries.data(),std::size_t(unitRegistry_.count)};}
    bool hitTank(const Simulation& sim,double x,double y) const;
    void writePpm(const std::filesystem::path& path) const;
};
}
