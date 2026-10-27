// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelShadowWorld.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelPalette vpl;IndexRemap remap{};UnitVoxelDrawInputs input;
    UnitVoxelShadowWorldState state;UnitVoxelWorldServices s;bool called=false;s.actor.originalTypeVisible=[&]{called=true;};
    std::vector<std::uint16_t> colors(16,0xabcd),depth(16,65535),alpha(16,127);std::vector<Palette16> palettes(53);
    VoxelModel model;
    for(const auto* body:std::array<const VoxelModel*,2>{nullptr,&model}){
        bool caught=false;try{drawHealthyUnitVoxelAndShadowToWorld(data,light,{body,nullptr,nullptr},{nullptr,nullptr,nullptr},
            vpl,input,false,false,false,state,s,remap,{4,4,colors,depth,alpha,palettes});}catch(const std::invalid_argument&){caught=true;}
        if(!caught||called||state.unit.pool.cursor||state.shadow.size()||state.unit.indexes[0].size()||colors!=std::vector<std::uint16_t>(16,0xabcd))
            throw std::runtime_error("Invalid Unit shadow body changed persistent state");
    }
}
