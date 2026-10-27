// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace ra2 {
// Presentation adapter observed from the supplied GI Ready/Walk SHP frames:
// N,NW,W,SW,S,SE,E,NE in screen space. Simulation facing starts at map north
// (screen NE) and increases clockwise. Sector rounding remains supplied; this
// is not recovery of the original Infantry drawing/sequence routine.
constexpr unsigned giSpriteDirection(std::uint16_t heading){
    return (7u-((unsigned(heading)+4096u)>>13))&7u;
}
}
