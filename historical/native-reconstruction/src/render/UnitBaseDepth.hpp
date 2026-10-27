// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellAttributes.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
struct UnitBaseDepthInputs {
    Coord location;
    Facing facing;
    int tick=0;
    double heightScale=0;
    int currentRamp=-1,neighborRamp=-1,rock=3;
    // A false dimensions result leaves the supplied caller scratch untouched.
    int dimensionHeight=0,defaultTile=0;
};
struct UnitBaseDepthWorld {
    std::function<const MapCellAttributes&(MapInputPosition)> cell;
    std::span<const MapTileAttributes> tiles;
    std::span<const MapOverlayType> overlays;
    // Read-only observations: height, coordinates, facing, dimensions.
    std::function<void(int)> query;
    std::function<void(int,int)> dimensions;
};
struct UnitBaseDepthResult {int depth=0,dimensionHeight=0;};
// Ordinary Unit branch: kind 1, special state zero, nonharvester. Construction
// and alternate branches are excluded. Stable map records/fallback are required.
UnitBaseDepthResult ordinaryUnitBaseDepth(const UnitBaseDepthInputs&,const UnitBaseDepthWorld&);
}
