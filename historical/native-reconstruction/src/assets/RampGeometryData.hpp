// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <array>
#include <string_view>
namespace ra2 {
struct RampGeometryData {
    std::array<float,4096> tangent{};
    double tangentScale=0;
};
// A separate private prepared artifact; only the supplied patched profile is verified.
RampGeometryData readRampGeometryData(const Data&,std::string_view expectedSource={});
}
