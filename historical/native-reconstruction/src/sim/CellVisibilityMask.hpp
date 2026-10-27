// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellVisibilityState.hpp"
#include <cstdint>
#include <functional>
#include <span>

namespace ra2 {
using CellVisibilityMaskCell=CellVisibilityState;
struct CellVisibilityMaskWorld {
    std::span<CellVisibilityMaskCell* const> cells;
    CellVisibilityMaskCell* fallback=nullptr;
    std::function<void(TerrainCellPoint)> fallbackStore;
    std::function<void(TerrainCellPoint,int)> query;
};

// Complete base6A8D40. The 256 signed result entries are startup-owned input;
// this routine neither derives nor owns them. Mode false reads +12C bit3 and
// mode true reads +140 bit1.
std::int32_t cellVisibilityMask(TerrainCellPoint,bool mode,
    std::span<const std::int8_t> results,const CellVisibilityMaskWorld&);
}
