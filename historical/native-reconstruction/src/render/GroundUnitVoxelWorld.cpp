// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/GroundUnitVoxelWorld.hpp"
#include "render/SharedGroundUnitVoxelWorld.hpp"
#include <algorithm>
#include "render/VoxelCache.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
// Borrow the actual owners throughout a call. The legacy profiles and shared
// profile use the same root; no cache/pool/image state is copied or leased.
struct GroundDrawView { bool& stagingSurface;bool& staging;PixelRect& dirty; };
struct GroundStagingView {
    GroundDrawView draw;
    UnitStaging& image;
    std::array<VoxelSnapshotIndex,3>& indexes;
    VoxelSnapshotPool& pool;
};
struct GroundWorldView { GroundStagingView unit;VoxelSnapshotIndex& shadow; };
GroundWorldView view(UnitVoxelShadowWorldState& s){
    return {{{s.unit.draw.stagingSurface,s.unit.draw.staging,s.unit.draw.dirty},
        s.unit.image,s.unit.indexes,s.unit.pool},s.shadow};
}
void emit(const UnitVoxelStore& s,char event,int value){if(s)s(event,value);}
Matrix applyBarrelPitch(const RasterData& data,Matrix pose,std::uint16_t heading) {
    // The ordinary flat/zero-offset branch pivots around the turret matrix's
    // zero translation. Original 0x590880 rotates columns X/Z, unlike the
    // body/turret rotation of columns X/Y. Keep the float32 angle store.
    const float angle=float(-((voxelHeading(heading)-8)*data.headingStep));
    const double c=tableCosine(data,angle),s=tableSine(data,angle);
    for(int row=0;row<3;++row) {
        const int x=row*4,z=x+2;const double a=pose[x],b=pose[z];
        pose[x]=float(a*c-b*s);pose[z]=float(a*s+b*c);
    }
    return pose;
}
}
static void drawGroundRoot(const RasterData& data,const UnitVoxelDrawInputs& in,
                          GroundDrawView state,const UnitVoxelDrawServices& s,
                          const GroundUnitShadowServices& ground,
                          const std::function<void(const UnitVoxelShadowRequest&,PixelPoint)>& shadow,
                          bool heightAware,const GroundUnitBodyServices* body,
                          const UnitVoxelStore& store={}) {
    if(in.bodyFrames<=0)throw std::invalid_argument("Positive body HVA frame count required");
    if(state.staging||state.stagingSurface)throw std::invalid_argument("Unit voxel drawing requires the ordinary world surface");
    OriginalRounding rounding;
    s.originalTypeVisible();
    const int frame=in.animationFrame%in.bodyFrames;
    const bool previousSurface=state.stagingSurface;
    state.stagingSurface=true;emit(store,'s',1);
    const auto bounds=s.stagingBounds();
    state.staging=true;emit(store,'f',1);
    std::int32_t seed=in.keyGate?0:-1;
    Matrix bodyPose;
    if(body)bodyPose=body->pose(&seed);
    else {s.bodyPose();bodyPose=voxelBodyMatrix(data,in.bodyHeading);seed=in.keyGate?voxelHeading(in.bodyHeading):-1;}
    const auto bodyKey=bodyVoxelKey(seed,frame);
    // Four ordered assignments, even when an earlier draw left a dirty region.
    state.dirty.x=in.emptyDirty.x;emit(store,'0',state.dirty.x);
    state.dirty.y=in.emptyDirty.y;emit(store,'1',state.dirty.y);
    state.dirty.width=in.emptyDirty.width;emit(store,'2',state.dirty.width);
    state.dirty.height=in.emptyDirty.height;emit(store,'3',state.dirty.height);
    auto part=[&](UnitVoxelPart which,int key,int partFrame,const Matrix& pose) {
        FootLitRequest call;call.model=std::uint32_t(which);call.cache=call.model;
        call.frame=partFrame;call.key=key;call.clip=bounds;call.point={128,128};
        call.pose=pose;call.brightness=in.brightness;call.flags=0x2800;
        if(body&&body->observePart)body->observePart(which,key,pose);
        drawFootLit(call,true,s.drawOffset,s.lit);
    };
    part(UnitVoxelPart::Body,bodyKey,frame,voxelMultiply(in.camera,bodyPose));
    const int turretKey=turretVoxelKey(bodyKey,in.turretHeading,0);
    s.multipleTurretQuery();
    const bool turretCached=turretKey!=-1&&in.turretCacheHasEntries&&s.cachedImage(UnitVoxelPart::Turret,turretKey);
    const bool barrelCached=in.barrelModel&&turretKey!=-1&&s.cachedImage(UnitVoxelPart::Barrel,turretKey);
    Matrix turretPose,barrelPose;
    if(turretCached&&(!in.barrelModel||barrelCached)) {
        // These are intentionally the untransformed body matrix. A warm image
        // makes the geometry unused by the child; the caller still forwards it.
        turretPose=bodyPose;barrelPose=bodyPose;
    } else {
        auto pose=body?bodyPose:voxelBodyMatrix(data,in.bodyHeading);
        // Stock TurretOffset is zero. Rotate the actual locomotor matrix, not a
        // fresh flat heading matrix. Preserve the float32 angle boundary.
        const float angle=float((voxelHeading(in.turretHeading)-8)*data.headingStep-
                                (voxelHeading(in.bodyHeading)-8)*data.headingStep);
        const double c=tableCosine(data,angle),sine=tableSine(data,angle);
        for(int row=0;row<3;++row){const int a=row*4;const double x=pose[a],y=pose[a+1];
            pose[a]=float(y*sine+x*c);pose[a+1]=float(y*c-x*sine);}
        const Vec3 pivot{pose[3],pose[7],pose[11]};
        auto barrel=pose;
        const auto translate=[](Matrix& m,Vec3 v){
            // 0x5900F0 stores X/Y accumulators after each component; its Z
            // accumulator survives the intermediate stores at full precision.
            for(int row=0;row<2;++row){const int a=row*4;
                const float x=float(double(v.x)*m[a]+m[a+3]);
                const float y=float(double(v.y)*m[a+1]+x);
                m[a+3]=float(double(v.z)*m[a+2]+y);}
            m[11]=float((double(v.z)*m[10])+
                (double(v.y)*m[9]+(double(v.x)*m[8]+m[11])));
        };
        translate(barrel,{-pivot.x,-pivot.y,-pivot.z});
        barrel=applyBarrelPitch(data,barrel,in.barrelHeading);
        translate(barrel,pivot);
        turretPose=voxelMultiply(in.camera,pose);
        barrelPose=voxelMultiply(in.camera,barrel);
    }
    s.multipleTurretQuery();
    if(!barrelAfterTurret(in.turretHeading)&&in.barrelModel)
        part(UnitVoxelPart::Barrel,turretKey,0,barrelPose);
    part(UnitVoxelPart::Turret,turretKey,frame,turretPose);
    if(barrelAfterTurret(in.turretHeading)&&in.barrelModel)
        part(UnitVoxelPart::Barrel,turretKey,0,barrelPose);
    const int brightness=s.finalBrightness(in.brightness);s.status();
    s.finalDraw(in.point,in.clip,brightness);
    const auto dirty=state.dirty;
    state.stagingSurface=previousSurface;emit(store,'s',int(previousSurface));
    state.staging=false;emit(store,'f',0);
    int shadowKey=int((std::uint32_t(bodyKey)>>5)&1023u);
    const auto shadowPose=ground.pose(&shadowKey);
    // The first value is used only by excluded add-14/bridge branches. Still
    // execute the query before the explicit current-Cell lookup.
    ground.relativeHeight();s.cell();
    const auto predicate=s.predicate();
    if(predicate>1)throw std::invalid_argument("Ground Unit predicate outside ordinary profile");
    if(!predicate) {
        if(ground.relativeHeight()<=0)
            shadowKey=signed32(std::uint32_t(shadowKey)|0x80000000u);
        else shadowKey=-1;
    }
    const bool elevated=ground.relativeHeight()>0;
    if(elevated&&!heightAware)
        throw std::invalid_argument("Elevated Unit shadow matrix/point branch requires recovery");
    // Unit evaluates Y and X through distinct getters; Foot obtains both once
    // again for the wrapped world point. The first two values are stencil origins.
    const auto rawY=ground.point().y;
    // Unit's positive-height branch increments only the stencil Y, before the
    // independent X query. Foot's later world point remains unincremented.
    const auto y=elevated?signed32(std::uint32_t(rawY)+1u):rawY;
    const auto x=ground.point().x;
    const auto offset=ground.point();
    const PixelPoint at{signed32(std::uint32_t(in.point.x)+std::uint32_t(offset.x)),
                        signed32(std::uint32_t(in.point.y)+std::uint32_t(offset.y))};
    shadow({shadowKey,at,in.clip,voxelMultiply(in.camera,shadowPose),!predicate},{x,y});
    s.clearStaging(dirty);
}
static void drawGroundStaging(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableCache,
    GroundStagingView state,const UnitVoxelStagingServices& s,const IndexRemap& remap,const GroundUnitShadowServices& ground,
    const std::function<void(const UnitVoxelShadowRequest&,PixelPoint)>& shadow,bool heightAware,const GroundUnitBodyServices* body,
    const UnitVoxelStore& store){
    if(input.bodyFrames!=1||!animations[0]||animations[0]->frames!=1)
        throw std::invalid_argument("Unit staging requires the stock one-frame body HVA");
    if(state.image.pixels.size()!=65536)throw std::invalid_argument("Unit staging requires a 256 by 256 byte surface");
    for(int v:{input.emptyDirty.x,input.emptyDirty.y,input.emptyDirty.width,input.emptyDirty.height})
        if(v<-1048576||v>1048576)throw std::invalid_argument("Unit staging template outside bounded profile");
    auto in=input;in.turretCacheHasEntries=state.indexes[1].size()!=0;in.barrelModel=models[2]!=nullptr;
    UnitVoxelDrawServices bound;
    bound.originalTypeVisible=s.originalTypeVisible;bound.bodyPose=s.bodyPose;
    bound.multipleTurretQuery=s.multipleTurretQuery;bound.shadowPose=s.shadowPose;
    bound.finalBrightness=s.finalBrightness;bound.status=s.status;
    bound.finalDraw=s.finalDraw;bound.height=s.height;bound.cell=s.cell;
    bound.predicate=s.predicate;bound.shadow=s.shadow;
    bound.stagingBounds=[]{return PixelRect{0,0,256,256};};
    bound.drawOffset=driveLitDrawOffset;
    bound.cachedImage=[&](UnitVoxelPart part,int key){return state.indexes[std::size_t(part)].find(key).has_value();};
    bound.lit=[&](const FootLitRequest& r){
        const auto part=std::size_t(r.model);
        if(part>=3)throw std::invalid_argument("Unknown Unit staging part");
        state.image.dirty=state.draw.dirty;
        drawOrdinaryTechnoVoxelPart(data,light,models[part],animations[part],vpl,r,
            disableCache,&state.indexes[part],state.pool,s.part,remap,state.image);
        state.draw.dirty=state.image.dirty;
    };
    bound.clearStaging=[&](PixelRect r){
        // Original BSurface Fill clips the saved dirty region to its bounds.
        // Bounds above and stagingUnion keep these additions in int range.
        const int left=std::max(0,r.x),top=std::max(0,r.y);
        const int right=std::min(256,r.x+r.width),bottom=std::min(256,r.y+r.height);
        if(r.width<=0||r.height<=0||right<=left||bottom<=top)return;
        for(int y=top;y<bottom;++y)std::fill(state.image.pixels.begin()+y*256+left,state.image.pixels.begin()+y*256+right,0);
    };
    drawGroundRoot(data,in,state.draw,bound,ground,shadow,heightAware,body,store);
}
static void drawGroundWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableCache,
    GroundStagingView state,const UnitVoxelWorldServices& s,const IndexRemap& remap,UnitVoxelWorldPlanes world,const GroundUnitShadowServices& ground,
    const std::function<void(const UnitVoxelShadowRequest&,PixelPoint)>& shadow,bool heightAware,const GroundUnitBodyServices* body,
    const UnitVoxelStore& store){
    if(world.width<1||world.height<1||world.width>4096||world.height>4096||
       world.colors.size()!=std::size_t(world.width)*world.height||world.depth.size()!=world.colors.size()||
       world.alpha.size()!=world.colors.size()||world.palettes.size()!=53)
        throw std::invalid_argument("Unit world requires matched planes and 53 palette rows");
    const auto clip=input.clip;
    if(clip.x<0||clip.y<0||clip.width<0||clip.height<0||
       std::int64_t(clip.x)+clip.width>world.width||std::int64_t(clip.y)+clip.height>world.height)
        throw std::invalid_argument("Unit world clip must be contained in destination");
    FootDepthServices depth;
    depth.locomotorDepth=[]{return 0;};depth.locomotorGradient=[]{return 2;};
    depth.type=[&]{return FootDepthType{s.metadata.zFudgeColumn,s.metadata.zFudgeTunnel,s.metadata.zFudgeCliff,s.metadata.zFudgeBridge};};
    depth.predicate0=[&]{return footDepthPredicate0(s.map);};depth.predicate1=[&]{return footDepthPredicate1(s.map);};
    depth.predicate2=[&]{return footDepthPredicate2(s.map);};depth.predicate3=[&]{return std::uint8_t(footDepthFlag(s.map));};
    depth.baseDepth=s.baseDepth;
    const auto z=[&]{return footDepthAdjustment(true,depth);};const auto gradient=[&]{return footDepthGradient(true,depth);};
    auto actor=s.actor;actor.part.value2C0=z;actor.part.value2C4=gradient;
    actor.finalDraw=[&](PixelPoint p,PixelRect r,int brightness){
        UnitSurfaceInputs in;in.point=p;in.clip=r;in.dirty=state.draw.dirty;in.brightness=brightness;
        in.typeBAE=s.metadata.tooBigToFitUnderBridge;
        UnitSurfaceServices surface;
        surface.layer=[]{return 0;};surface.flag204=surface.flag205=surface.disguised=[]{return std::uint8_t(0);};
        surface.ownerVisible=[]{return false;};surface.houseBlitter=[](auto flags){return unitSurfaceBlitterSlot(flags);};
        surface.depth=z;surface.gradient=gradient;surface.sourceBounds=[]{return PixelRect{0,0,256,256};};
        surface.draw=[&](const UnitSurfaceRequest& call){
            if(s.surface)s.surface(call);
            if(call.blitter!=0x98||call.extra)throw std::invalid_argument("Alternate Unit world blitter requires recovery");
            if(call.gradient==0)blitUnitTopGradient(state.image.pixels,256,256,call.source,
                {call.destination.x,call.destination.y},call.clip,call.depth,call.brightness,world.palettes,world.width,world.height,world.colors,world.depth,world.alpha);
            else if(call.gradient==2)blitUnit(state.image.pixels,256,256,call.source,
                {call.destination.x,call.destination.y},call.clip,call.depth,call.brightness,world.palettes,world.width,world.height,world.colors,world.depth,world.alpha);
            else throw std::invalid_argument("Alternate Unit world gradient requires recovery");
        };
        auto bridge=s.contact;bridge.flag100=[&]{return std::uint8_t(footDepthFlag(s.map));};bridge.predicate0=[&]{return footDepthPredicate0(s.map);};
        drawBridgeUnitSurface(in,s.actor494,bridge,surface);
    };
    drawGroundStaging(data,light,models,animations,vpl,input,disableCache,state,actor,remap,ground,shadow,heightAware,body,store);
}
static void drawGroundProfile(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,GroundWorldView state,
    const UnitVoxelWorldServices& s,const GroundUnitShadowServices& ground,const IndexRemap& remap,UnitVoxelWorldPlanes world,bool heightAware,const GroundUnitBodyServices* body,
    const UnitVoxelStore& store={}){
    if(!ground.pose||!ground.relativeHeight||!ground.point)throw std::invalid_argument("Ground Unit requires pose and height services");
    if(!models[0]||models[0]->sections.size()!=1)
        throw std::invalid_argument("Unit shadow join requires a loaded one-section body");
    FootDepthServices depth;
    depth.locomotorDepth=[]{return 0;};depth.locomotorGradient=[]{return 2;};
    depth.type=[&]{return FootDepthType{s.metadata.zFudgeColumn,s.metadata.zFudgeTunnel,s.metadata.zFudgeCliff,s.metadata.zFudgeBridge};};
    depth.predicate0=[&]{return footDepthPredicate0(s.map);};depth.predicate1=[&]{return footDepthPredicate1(s.map);};
    depth.predicate2=[&]{return footDepthPredicate2(s.map);};depth.predicate3=[&]{return std::uint8_t(footDepthFlag(s.map));};
    depth.baseDepth=s.baseDepth;
    CachedVoxelPartServices shadow;
    shadow.kind=s.actor.part.kind;shadow.selectBlitter=s.actor.part.selectBlitter;
    shadow.value2C0=[&]{return footDepthAdjustment(true,depth);};
    shadow.value2C4=[&]{return footDepthGradient(true,depth);};
    auto services=s;
    const auto drawShadow=[&](const UnitVoxelShadowRequest& request,PixelPoint origin){
        if(state.unit.draw.staging||state.unit.draw.stagingSurface)
            throw std::invalid_argument("Unit shadow requires restored world state");
        if(ground.observeShadow)ground.observeShadow(request,origin);
        if(s.actor.shadow)s.actor.shadow(request);
        ShadowVoxelWorldInputs in;in.cache={request.key,false,noShadow,false,true,disableShadowCache,true};
        in.pose=request.pose;in.point=request.point;in.clip=request.clip;
        if(request.useStagingStencil)in.stencil={state.unit.image.pixels,256,256,origin};
        drawOrdinaryShadowVoxelToWorld(data,light,models[0],animations[0],in,&state.shadow,state.unit.pool,shadow,
            world.width,world.height,world.colors,world.depth,state.unit.draw.dirty);
    };
    drawGroundWorld(data,light,models,animations,vpl,input,disableLitCache,state.unit,services,remap,world,ground,drawShadow,heightAware,body,store);
}
void drawGroundUnitVoxelToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState& state,
    const UnitVoxelWorldServices& s,const GroundUnitShadowServices& ground,const IndexRemap& remap,UnitVoxelWorldPlanes world){
    drawGroundProfile(data,light,models,animations,vpl,input,disableLitCache,noShadow,disableShadowCache,view(state),s,ground,remap,world,false,nullptr);
}
void drawHeightAwareGroundUnitVoxelToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState& state,
    const UnitVoxelWorldServices& s,const GroundUnitShadowServices& ground,const IndexRemap& remap,UnitVoxelWorldPlanes world){
    drawGroundProfile(data,light,models,animations,vpl,input,disableLitCache,noShadow,disableShadowCache,view(state),s,ground,remap,world,true,nullptr);
}
void drawPosedGroundUnitVoxelToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState& state,
    const UnitVoxelWorldServices& s,const GroundUnitBodyServices& body,
    const GroundUnitShadowServices& ground,const IndexRemap& remap,UnitVoxelWorldPlanes world){
    if(!body.pose)throw std::invalid_argument("Posed Unit requires an actual body pose service");
    drawGroundProfile(data,light,models,animations,vpl,input,disableLitCache,noShadow,disableShadowCache,view(state),s,ground,remap,world,true,&body);
}
void drawSharedPosedGroundUnitVoxelToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,SharedUnitVoxelStage& stage,
    UnitVoxelWorldTypeIndexes& type,UnitVoxelActorStage& actor,
    const UnitVoxelWorldServices& s,const GroundUnitBodyServices& body,
    const GroundUnitShadowServices& ground,const IndexRemap& remap,UnitVoxelWorldPlanes world,
    const UnitVoxelStore& store){
    if(!body.pose)throw std::invalid_argument("Shared posed Unit requires an actual body pose service");
    GroundWorldView storage{{{stage.stagingSurface,actor.staging,stage.image.dirty},
        stage.image,type.lit.parts,stage.pool},type.shadow};
    drawGroundProfile(data,light,models,animations,vpl,input,disableLitCache,noShadow,
        disableShadowCache,storage,s,ground,remap,world,true,&body,store);
}

}
