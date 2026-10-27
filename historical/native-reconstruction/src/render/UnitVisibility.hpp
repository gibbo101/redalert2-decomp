// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TerrainVisibility.hpp"
#include <utility>
namespace ra2 {
struct UnitVisibilityServices {
    std::function<Coord()> coordinates;
    std::function<std::pair<PixelPoint,bool>(Coord)> project;
    std::function<void(PixelPoint,PixelRect)> draw;
};
// Unit +0x370 must be zero. The wrapper forces its third argument to zero.
// onMap is not read by this ordinary Object gate. viewport is a live reference:
// bounds may alias it, as in the actual per-frame caller.
bool drawOrdinaryUnitIfVisible(TerrainMarkState&,PixelRect& bounds,const PixelRect& viewport,
                              TerrainDrawGate,std::uint8_t specialDrawState,
                              const UnitVisibilityServices&,const TerrainVisibilityTrace& trace={});
}
