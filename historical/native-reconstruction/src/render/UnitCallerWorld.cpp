// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitCallerWorld.hpp"
#include <stdexcept>
namespace ra2 {
void drawHealthyUnitCallerToWorld(const RasterData& data,const RenderData& light,
    const std::array<const VoxelModel*,3>& models,const std::array<const Animation*,3>& animations,
    const VoxelPalette& vpl,UnitDrawResource& resource,const OrdinaryUnitDrawInputs& actor,
    PixelPoint point,PixelRect clip,const UnitVoxelDrawInputs& input,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState& state,
    const UnitCallerWorldServices& s,const IndexRemap& remap,UnitVoxelWorldPlanes world,
    const UnitDrawTrace& trace){
    if(actor.addFourteen||!actor.type.voxel||!actor.type.voxelModel||actor.timerStart!=-1||actor.timerDuration)
        throw std::invalid_argument("Unsupported healthy Unit caller/world profile");
    auto caller=s.caller;
    caller.originalTypeVisible=[&]{
        const auto visible=s.caller.originalTypeVisible();
        if(!visible)throw std::invalid_argument("Alternate Unit world type is unrecovered");
        return visible;
    };
    caller.draw=[&](bool voxel,PixelPoint p,PixelRect r,int brightness){
        if(!voxel)throw std::invalid_argument("SHP Unit world drawing is unrecovered");
        if(s.caller.draw)s.caller.draw(voxel,p,r,brightness);
        auto in=input;in.point=p;in.clip=r;in.brightness=brightness;
        drawHealthyUnitVoxelAndShadowToWorld(data,light,models,animations,vpl,in,
            disableLitCache,noShadow,disableShadowCache,state,s.world,remap,world);
    };
    drawOrdinaryUnitCaller(resource,actor,point,clip,caller,trace);
}
}
