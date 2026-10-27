// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "sim/Drive.hpp"
#include <array>
namespace ra2 {
struct MapRampPlane {double x=0,y=0,offset=0,limit=0,add=0;};
struct MapFloorHeightState {
    std::uint8_t flags=0;
    double height=0,scale=0;
    std::array<MapRampPlane,20> planes{};
};
// Recovered lazy initialization and finite numeric Cell query. The initial
// global/template state and current level-height global are supplied. The three
// lazy bits are independent; changing the live height does not reset cached data.
// No original static initialization, concurrent mutation or NaN/overflow claim.
int cellFloorHeight(MapFloorHeightState&,int levelHeight,std::int8_t level,
    std::uint8_t ramp,int worldX,int worldY);
struct MapFloorHeightWorld {
    std::span<MapCellInput* const> cells;
    MapCellInput* fallback=nullptr;
    std::function<void(MapInputPosition)> fallbackStore;
};
// Uses full signed division before the wrapped combined index; do not substitute
// a lookup that first truncates each coordinate to a word or checks X/Y separately.
int mapFloorHeight(MapFloorHeightState&,int levelHeight,Coord,const MapFloorHeightWorld&);
int relativeMapHeight(MapFloorHeightState&,int levelHeight,Coord,
    std::uint8_t bridge,int bridgeHeight,const MapFloorHeightWorld&);
Coord mapCellCenterHeight(MapFloorHeightState&,int levelHeight,const MapCellInput&);
}
