// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellVisibilityState.hpp"
#include "sim/VisibilityStartup.hpp"
#include <functional>
#include <span>

namespace ra2 {
struct PostSightRefreshWorld {
    std::span<CellVisibilityState* const> cells;
    CellVisibilityState* fallback=nullptr;
    std::function<void(TerrainCellPoint)> fallbackStore;
    std::function<void(TerrainCellPoint,int)> query;
};
struct PostSightRefreshServices {
    std::function<std::uint8_t(TerrainCellPoint)> visibilityMask;
    std::function<void(int)> redraw;
    std::function<void(char,std::int32_t,std::int32_t,std::int32_t)> trace;
};

// Complete base54A550 post-sight primary-mask refresh. Runtime-initialized
// spread points/projection scale and map/effect owners remain explicit inputs.
void refreshPostSightVisibility(Coord coordinates,std::int32_t innerRadius,
    std::int32_t outerRadius,std::uint32_t disabled,
    const PostSightRefreshWorld&,const VisibilityStartup&,
    const PostSightRefreshServices&);
}
