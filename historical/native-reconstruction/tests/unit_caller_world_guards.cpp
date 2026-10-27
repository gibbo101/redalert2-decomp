// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitCallerWorld.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelPalette vpl;IndexRemap remap{};UnitVoxelDrawInputs input;
    UnitVoxelShadowWorldState state;UnitCallerWorldServices services;bool called=false;
    services.caller.loadShape=[&]{called=true;return 0u;};UnitDrawResource resource;
    std::vector<std::uint16_t> colors(16,0xabcd),depth(16,65535),alpha(16,127);std::vector<Palette16> palettes(53);
    for(int mode=0;mode<5;++mode){
        OrdinaryUnitDrawInputs actor;
        if(mode==0)actor.addFourteen=1;
        if(mode==1)actor.type.voxel=0;
        if(mode==2)actor.type.voxelModel=false;
        if(mode==3)actor.timerStart=0;
        if(mode==4)actor.timerDuration=1;
        bool caught=false;try{drawHealthyUnitCallerToWorld(data,light,{nullptr,nullptr,nullptr},{nullptr,nullptr,nullptr},vpl,resource,
            actor,{0,0},{0,0,4,4},input,false,false,false,state,services,remap,{4,4,colors,depth,alpha,palettes});}
        catch(const std::invalid_argument&){caught=true;}
        if(!caught||called||resource.flags||state.unit.pool.cursor||colors!=std::vector<std::uint16_t>(16,0xabcd))
            throw std::runtime_error("Unsupported Unit caller changed state");
    }
}
