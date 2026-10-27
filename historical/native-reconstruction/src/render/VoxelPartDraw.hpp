// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
struct StagedVoxelPartInputs {
    Matrix pose{};
    int frame=0,brightness=0;
    std::uint32_t flags=0x2800;
    PixelPoint point{128,128};
    PixelRect clip{0,0,256,256};
};
struct StagedVoxelPartServices {
    std::function<std::uint8_t()> flag204,flag205,house,predicateC0;
    std::function<std::uint32_t(std::uint32_t)> adjustFlags;
    std::function<void()> kind;
    std::function<int()> value2C4,value2C0;
    std::function<void(std::uint32_t)> selectBlitter;
    std::function<void(const RasterFrame&,PixelPoint,PixelRect,int,int,int)> draw;
};
// Complete ordinary part-render wrapper, one loaded section, optional supplied
// HVA, Unit kind 1, staging surface/byte set, identity global matrix and ordinary
// light. Blitter selection/draw and actor/house/value associations are services.
// Flag bit 8 and nonstaging clip-height branches require separate recovery.
RasterFrame drawStagedVoxelPart(const RasterData&,const RenderData&,const VoxelModel&,
    const Animation*,const VoxelPalette&,const StagedVoxelPartInputs&,
    const StagedVoxelPartServices&);
}
