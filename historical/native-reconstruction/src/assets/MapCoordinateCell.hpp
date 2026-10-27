// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapFloorHeight.hpp"
namespace ra2 {
// Full signed world-coordinate division and wrapped combined map index. A miss
// returns the shared fallback and stores word coordinates there. Table storage
// and original +0x13C count remain supplied; oversized counts are refused safely.
MapCellInput& mapCoordinateCell(Coord,const MapFloorHeightWorld&,int count);
}
