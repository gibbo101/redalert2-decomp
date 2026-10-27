// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelShadowWorld.hpp"
#include <stdexcept>
namespace ra2 {
void drawHealthyUnitVoxelAndShadowToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState& state,
    const UnitVoxelWorldServices& s,const IndexRemap& remap,UnitVoxelWorldPlanes world){
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
    services.actor.shadow=[&](const UnitVoxelShadowRequest& request){
        if(state.unit.draw.staging||state.unit.draw.stagingSurface)
            throw std::invalid_argument("Unit shadow requires restored world state");
        if(s.actor.shadow)s.actor.shadow(request);
        ShadowVoxelWorldInputs in;in.cache={request.key,false,noShadow,false,true,disableShadowCache,true};
        in.pose=request.pose;in.point=request.point;in.clip=request.clip;
        if(request.useStagingStencil)in.stencil={state.unit.image.pixels,256,256,{0,0}};
        drawOrdinaryShadowVoxelToWorld(data,light,models[0],animations[0],in,&state.shadow,state.unit.pool,shadow,
            world.width,world.height,world.colors,world.depth,state.unit.draw.dirty);
    };
    drawHealthyUnitVoxelToWorld(data,light,models,animations,vpl,input,disableLitCache,state.unit,services,remap,world);
}
}
