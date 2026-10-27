// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootVoxelStaging.hpp"
#include <stdexcept>
using namespace ra2;
int main(){
    RasterData data;RenderData light;VoxelPalette vpl;FootLitRequest request;
    VoxelSnapshotIndex index;VoxelSnapshotPool pool{Bytes(64,0xa5)};UnitStaging stage;
    const auto initial=stage.pixels;IndexRemap remap{};StagedVoxelPartServices services;
    services.flag204=services.flag205=services.house=[]{return std::uint8_t(0);};
    auto run=[&]{return drawOrdinaryFootVoxelPart(data,light,nullptr,nullptr,vpl,request,true,false,&index,pool,services,remap,stage);};
    auto unchanged=[&]{if(pool.cursor||pool.bytes!=Bytes(64,0xa5)||index.size()||stage.pixels!=initial||
        stage.dirty.x||stage.dirty.y||stage.dirty.width||stage.dirty.height)
        throw std::runtime_error("Unsupported/invalid draw changed persistent state");};
    auto refused=[&]{bool caught=false;try{run();}catch(const std::invalid_argument&){caught=true;}
        if(!caught)throw std::runtime_error("Expected Foot staging domain refusal");unchanged();};
    request.flags=0;refused();request.flags=0x2800;
    services.flag204=[]{return std::uint8_t(1);};refused();services.flag204=[]{return std::uint8_t(0);};
    services.flag205=[]{return std::uint8_t(1);};refused();services.flag205=[]{return std::uint8_t(0);};
    services.house=[]{return std::uint8_t(1);};refused();services.house=[]{return std::uint8_t(0);};
    if(run().kind!=FootVoxelDrawKind::Skipped)throw std::runtime_error("Invalid cold model was not skipped");
    unchanged();
}
