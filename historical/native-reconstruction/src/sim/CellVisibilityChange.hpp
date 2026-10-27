// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellVisibilityState.hpp"
#include <cstdint>
#include <functional>
#include <span>

namespace ra2 {
using CellVisibilityChangeCell=CellVisibilityState;
struct CellVisibilityChangeWorld {
    std::span<CellVisibilityChangeCell* const> cells;
    CellVisibilityChangeCell* fallback=nullptr;
    std::function<void(TerrainCellPoint)> fallbackStore;
    std::function<void(TerrainCellPoint,int)> query;
};
struct CellVisibilityChangeServices {
    // Base6A8D40 remains a supplied visibility-mask calculator at this boundary.
    std::function<std::uint8_t(TerrainCellPoint,bool)> visibilityValue;
    std::function<void(int)> redraw;
    std::function<void(int,int,bool)> discover;
    std::function<void(int)> refresh;
    std::function<void(char,std::int32_t,std::int32_t,std::int32_t)> trace;
};

// Complete base62FCA0 -> base499FC0 with exact low-byte selection between
// decrement47C840 and increment47C8A0.
bool changeCellVisibility(TerrainCellPoint,int house,
    std::uint32_t finalArgument,const CellVisibilityChangeWorld&,
    std::uint32_t refreshRules,const CellVisibilityChangeServices&);

// The original dereferences global A3D290 only after redraw/discovery and the
// live Cell140/entry-bit gates. The getter must reread that association, not a
// saved pointer or value. The scalar facade above supplies a fixed snapshot.
bool changeCellVisibilityWithLiveRefreshFlags(TerrainCellPoint,int house,
    std::uint32_t finalArgument,const CellVisibilityChangeWorld&,
    const std::function<std::uint32_t()>& scenarioFlags,
    const CellVisibilityChangeServices&);

// Legacy stock-E1 reveal facade retains the final-argument-zero guard.
bool revealCellForOrdinarySight(TerrainCellPoint,int house,
    std::uint32_t finalArgument,const CellVisibilityChangeWorld&,
    std::uint32_t refreshRules,const CellVisibilityChangeServices&);
}
