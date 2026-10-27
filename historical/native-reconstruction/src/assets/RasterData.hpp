// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <string_view>
#include "assets/Formats.hpp"
namespace ra2 {
struct RasterData {
    std::array<std::array<std::int32_t,9>,8> traversal{};
    std::array<float,10240> sine{};
    float sineScale=0,cosineScale=0;
    double headingStep=0,degrees=0;
};
RasterData readRasterData(const Data&,std::string_view expectedSource={});
}
