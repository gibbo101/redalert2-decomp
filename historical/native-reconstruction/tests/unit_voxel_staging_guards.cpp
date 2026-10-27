// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelStaging.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelPalette vpl;IndexRemap remap{};
    Animation hva;hva.frames=1;UnitVoxelDrawInputs in;UnitVoxelStagingState state;
    const auto original=state.image.pixels;UnitVoxelStagingServices s;bool called=false;
    s.originalTypeVisible=[&]{called=true;};
    auto run=[&](const Animation* body){drawHealthyUnitVoxelIntoStaging(data,light,{nullptr,nullptr,nullptr},{body,&hva,&hva},vpl,in,false,state,s,remap);};
    auto refused=[&](const Animation* body){bool caught=false;try{run(body);}catch(const std::invalid_argument&){caught=true;}
        if(!caught||called||state.pool.cursor||state.indexes[0].size()||state.draw.staging||state.draw.stagingSurface)
            throw std::runtime_error("Unit staging refusal changed persistent state");};
    refused(nullptr);hva.frames=2;refused(&hva);hva.frames=1;
    in.bodyFrames=2;refused(&hva);in.bodyFrames=1;
    in.emptyDirty={2147483647,0,1,1};refused(&hva);in.emptyDirty={};
    state.image.pixels.pop_back();refused(&hva);state.image.pixels=original;
    state.draw.staging=true;bool caught=false;try{run(&hva);}catch(const std::invalid_argument&){caught=true;}
    if(!caught||called||state.image.pixels!=original)throw std::runtime_error("Nested staging was not refused before callbacks");
}
