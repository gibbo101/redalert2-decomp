// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <functional>
#include <span>
namespace ra2 {
struct MapVisibilityCell {TerrainCellPoint point;std::uint32_t flags12c=0,flags140=0;std::int32_t count13c=0;};
struct MapVisibilityState {
    int heightDivisor=0,mode=0,overrideValue=0;
    std::uint8_t currentHouse13d=0;
};
struct MapVisibilityWorld {
    std::span<MapVisibilityCell* const> cells;
    MapVisibilityCell* fallback=nullptr;
    TerrainCellPoint direction3;
    // Observers are read-only. fallbackStore forwards the selected coordinate
    // assignment to other views of the same canonical Cell.
    std::function<void(char,TerrainCellPoint)> query;
    std::function<void(const MapVisibilityCell&,int)> neighbor;
    std::function<void(TerrainCellPoint)> fallbackStore;
    // Optional actual Cell owner lookup. Returns fields consumed immediately by
    // the predicate; no persistent mirror/table is needed. It performs the same
    // fallback assignment as a table lookup and must not substitute permission.
    std::function<MapVisibilityCell(TerrainCellPoint)> borrowedCell;
    std::function<void(const MapVisibilityCell&)> countRead; // Read-only diagnostic observer.
};
// Complete base predicates, including height projection and actual direction-3
// neighbor lookup. Flag names remain numeric; these do not implement fog drawing.
// Initial globals/Cells and the initialized direction offset remain supplied.
bool mapPrimaryVisibility(Coord,const MapVisibilityState&,const MapVisibilityWorld&);
bool mapSecondaryVisibility(Coord,const MapVisibilityState&,const MapVisibilityWorld&);
// Complete568280: signed positive count13C, independent of mode/House shortcuts.
bool mapCountVisibility(Coord,const MapVisibilityState&,const MapVisibilityWorld&);
}
