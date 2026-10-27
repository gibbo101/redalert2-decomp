// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
struct BuildingRenderBoundsState {
    PixelRect bounds50c{};
    Coord coordinates51c{};
    PixelPoint origin528{};
    bool operator==(const BuildingRenderBoundsState& other)const {
        return coordinates51c==other.coordinates51c&&origin528==other.origin528&&
            bounds50c.x==other.bounds50c.x&&bounds50c.y==other.bounds50c.y&&
            bounds50c.width==other.bounds50c.width&&bounds50c.height==other.bounds50c.height;
    }
};
struct BuildingRenderBoundsServices {
    std::function<Coord()> coordinatesA8;
    std::function<PixelPoint()> origin;
    std::function<PixelPoint(Coord)> project6a29d0;
    std::function<PixelRect()> typeBounds45e290;
    std::function<void(int,int)> store;
};
// Complete450DD0. Calls coordinates even on cache hits. Cached bounds and keys
// share the actual Building owner; no additional validity bit is synthesized.
const PixelRect& buildingRenderBounds(BuildingRenderBoundsState&,const BuildingRenderBoundsServices&);
}
