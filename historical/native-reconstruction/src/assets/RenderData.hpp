// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <string_view>
#include "assets/Formats.hpp"
namespace ra2 {
struct RenderData {
    std::array<std::vector<Vec3>,5> normals;
    double paletteCoefficient=0;
    float shadeScale=0,lightAngle=0;
    std::array<std::uint32_t,16384> sqrtMantissas{};
};
RenderData readRenderData(const Data& data,std::string_view expectedSource={});
struct VoxelPalette {
    std::uint32_t remapStart=0,remapEnd=0;
    Palette palette;
    std::vector<std::array<std::uint8_t,256>> sections;
    std::uint8_t lookup(std::uint8_t color,std::uint8_t shade) const;
};
VoxelPalette readVpl(const Data& data);
}
