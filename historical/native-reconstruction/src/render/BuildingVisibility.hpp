// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TerrainVisibility.hpp"
namespace ra2 {
struct BuildingVisibilityFields {
    const std::uint8_t& marked74;
    std::uint8_t& redraw75;
    const std::uint8_t& flag76;
    const std::uint8_t& hidden5b7;
};
struct BuildingVisibilityServices {
    std::function<std::uint8_t()> bypass;
    std::function<bool()> contextPresent;
    std::function<PixelRect()> bounds124;
    std::function<Coord()> coordinatesA8;
    std::function<PixelPoint(Coord)> project6a29d0;
    std::function<void(PixelPoint&,PixelRect&)> ordinary10c,special470;
    // Read-only diagnostics of original scalar reads and ordered parent stores.
    std::function<void(int,int)> read,store;
};
// Complete43A200. Both arguments use only their low byte, viewport is live,
// projection's boolean is ignored, and entered drawing children are required.
// Input clip is mutable, including when it aliases the live viewport.
bool drawBuildingIfVisible(BuildingVisibilityFields,PixelRect& clip,const PixelRect& viewport,
    std::int32_t force,std::int32_t special,const BuildingVisibilityServices&);
}
