// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include <array>
namespace ra2 {
struct MapAttributeLookup {
    std::span<MapCellInput* const> cells;
    MapCellInput* fallback=nullptr;
    std::function<void(MapInputPosition)> query,fallbackStore;
};
MapCellInput& mapAttributeCell(MapInputPosition,const MapAttributeLookup&);
// Supplied globals in exact documented address order, not named theater types.
using MapLATSettings=std::array<int,15>;
bool setupMapLAT(MapCellInput&,const MapLATSettings&,
    std::span<const MapInputPosition,8> directions,const MapAttributeLookup&,
    int residentRegistryCount,const std::function<void(int)>& tileStore={});
struct MapPermissionShape {int dimension0=0,originX=0,originY=0,width=0,height=0;};
bool mapCellPermitted(MapInputPosition,bool elevation,const MapPermissionShape&,
    const MapAttributeLookup&);
// Complete ordinary no-overlay/no-occupant passability decision. Map permission
// and float32 land speeds are supplied; loading/ownership and actors are separate.
int emptyCellPassability(const MapCellInput&,bool permitted,std::span<const float> landSpeeds);
}
