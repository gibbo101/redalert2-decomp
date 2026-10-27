// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <array>
#include <cstdint>

namespace ra2 {
struct VisibilityStartup {
    std::array<std::int32_t,11> radiusCounts{};
    std::array<TerrainCellPoint,369> offsets{};
    std::array<TerrainCellPoint,309> heightOffsets{};
    double heightProjectionScale=0.;
};

// Stock base startup state consumed by reveal-area. The private visibility-mask
// result table is a different caller-owned input and is deliberately absent.
VisibilityStartup initializeVisibilityStartup();
}
