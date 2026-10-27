// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelPartStaging.hpp"
#include <stdexcept>
namespace ra2 {
RasterFrame drawOrdinaryVoxelPartIntoStaging(const RasterData& data,const RenderData& light,
    const VoxelModel& model,const Animation* animation,const VoxelPalette& vpl,
    const StagedVoxelPartInputs& in,const StagedVoxelPartServices& actor,
    const IndexRemap& remap,Bytes& staging) {
    if(staging.size()!=256*256)throw std::invalid_argument("Voxel staging requires a 256x256 byte surface");
    auto services=actor;
    services.selectBlitter=[](std::uint32_t flags) {
        if(flags!=0u)throw std::invalid_argument("Alternate voxel staging blitter requires recovery");
    };
    services.draw=[&](const RasterFrame& frame,PixelPoint at,PixelRect clip,int,int,int) {
        const auto& b=frame.rectangle;
        blitIndexed(frame.pixels,256,256,{b[2],b[3],b[4],b[5]},at,clip,remap,256,256,staging);
    };
    return drawStagedVoxelPart(data,light,model,animation,vpl,in,services);
}
}
