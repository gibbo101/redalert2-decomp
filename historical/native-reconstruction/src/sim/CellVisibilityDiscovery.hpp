// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellClosestResident.hpp"
#include "sim/TerrainOccupation.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
struct CellVisibilityDiscoveryServices {
    // Initial scan point and later selected-Cell notification point are distinct reads.
    std::function<TerrainCellPoint(int)> point;
    // Return the actual Cell identity, including one shared fallback identity.
    // The callback owns the original lookup/fallback-coordinate side effect.
    std::function<int(TerrainCellPoint)> cellAt;
    std::function<std::int8_t(int)> level;
    std::function<CellClosestResidentServices(int)> residents;
    std::function<void(TerrainCellPoint)> notifyCell;
    std::function<void(int,int)> discoveredBy;
};

// Base 568520. A newly changed visibility Cell starts a seven-Cell diagonal
// projection. Each admitted Cell selects its nearest active primary resident at
// point zero, then dispatches that object's DiscoveredBy virtual with the House.
// Reveal-area production and its schedule remain separate callers.
void discoverVisibleCellResidents(int startingCell,int house,bool notify,
    const CellVisibilityDiscoveryServices&);
}
