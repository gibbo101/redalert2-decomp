// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelWorld.hpp"
#include <stdexcept>
namespace ra2 {
void drawHealthyUnitVoxelToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,const UnitVoxelDrawInputs& input,bool disableCache,
    UnitVoxelStagingState& state,const UnitVoxelWorldServices& s,const IndexRemap& remap,UnitVoxelWorldPlanes world){
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
    drawHealthyUnitVoxelIntoStaging(data,light,models,animations,vpl,input,disableCache,state,actor,remap);
}
}
