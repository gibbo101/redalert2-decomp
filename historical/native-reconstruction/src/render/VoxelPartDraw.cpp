// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelPartDraw.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
RasterFrame drawStagedVoxelPart(const RasterData& data,const RenderData& light,const VoxelModel& model,
    const Animation* animation,const VoxelPalette& vpl,const StagedVoxelPartInputs& in,
    const StagedVoxelPartServices& s) {
    if(model.sections.size()!=1)throw std::invalid_argument("Staged voxel part requires one section");
    if(in.flags&8u)throw std::invalid_argument("Staged voxel timer flag requires recovery");
    if(animation&&(animation->frames<=0||animation->names.size()!=1||
                   animation->transforms.size()!=std::size_t(animation->frames)))
        throw std::invalid_argument("Staged voxel HVA requires positive frames and one section");
    OriginalRounding rounding;
    const auto& section=model.sections.front();
    const auto shades=voxelSectionShades(data,light,section.normalType,in.pose);
    Matrix matrix=in.pose;
    if(animation) {
        // This wrapper uses unsigned DIV, unlike the Unit caller's signed IDIV.
        const auto frame=std::uint32_t(in.frame)%std::uint32_t(animation->frames);
        matrix=voxelMultiply(in.pose,animation->transforms[frame]);
    }
    matrix=voxelMultiply(voxelIdentity(),matrix);
    auto result=rasterVoxel(data,section,matrix,shades,vpl);
    auto flags=in.flags;
    if(s.flag204()!=0||s.flag205()!=0)flags|=4u;
    if(s.house()!=0&&s.predicateC0()!=0)flags=s.adjustFlags(flags);
    flags&=~16u;
    if(flags&8u)throw std::invalid_argument("Adjusted staged voxel timer flag requires recovery");
    s.kind();
    const int value2C4=s.value2C4(),value2C0=s.value2C0();
    s.selectBlitter(flags);
    const auto& b=result.rectangle;
    const PixelPoint at{signed32(std::uint32_t(in.point.x)+std::uint32_t(b[0])),
                        signed32(std::uint32_t(in.point.y)+std::uint32_t(b[1]))};
    s.draw(result,at,in.clip,value2C0,value2C4,in.brightness);
    return result;
}
}
