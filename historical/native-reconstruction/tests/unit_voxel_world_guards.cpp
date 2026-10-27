// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelWorld.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelPalette vpl;IndexRemap remap{};UnitVoxelDrawInputs input;
    UnitVoxelStagingState state;UnitVoxelWorldServices s;bool called=false;s.actor.originalTypeVisible=[&]{called=true;};
    std::vector<std::uint16_t> colors(16,0xabcd),depth(16,65535),alpha(16,127);std::vector<Palette16> palette(53);
    int width=4,height=4;
    auto refused=[&]{bool caught=false;try{drawHealthyUnitVoxelToWorld(data,light,{nullptr,nullptr,nullptr},{nullptr,nullptr,nullptr},vpl,input,false,state,s,remap,{width,height,colors,depth,alpha,palette});}catch(const std::invalid_argument&){caught=true;}
        if(!caught||called||colors!=std::vector<std::uint16_t>(16,0xabcd)||state.pool.cursor||state.indexes[0].size())throw std::runtime_error("Unit world refusal changed persistent state");};
    width=0;refused();width=4;palette.pop_back();refused();palette.resize(53);
    depth.pop_back();refused();depth.resize(16,65535);
    input.clip={1,0,4,4};refused();input.clip={0,-1,4,4};refused();
    input.clip={2147483647,0,2147483647,4};refused();input.clip={0,0,-1,4};refused();
}
