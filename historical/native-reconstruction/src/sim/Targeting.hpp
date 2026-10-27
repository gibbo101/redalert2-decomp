// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
namespace ra2 {
struct Coord;
// Original stored data, loaded from the fingerprinted supplied executable.
struct DirectionData {
    std::array<float,4097> atan{};
    float slopeStep=0,positiveHalfPi=0,negativeHalfPi=0;
    double pi=0,halfPi=0,angleScale=0;
};
// Recovered Object bearing helper, 0x5CAC70 -> 0x4BA120.
// Bounded to coordinate differences <= 2^20 leptons per component.
std::uint16_t destinationDirection(const DirectionData& data,Coord from,Coord target);
}
