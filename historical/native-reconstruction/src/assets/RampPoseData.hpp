// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
#include <string_view>
namespace ra2 {
struct RampPoseData {
    std::array<float,4097> inverseSine{};
    float inverseScale=0;
    double halfPi=0,oppositeHalfPi=0,epsilon=0;
};
RampPoseData readRampPoseData(const Data&,std::string_view expectedSource={});
}
