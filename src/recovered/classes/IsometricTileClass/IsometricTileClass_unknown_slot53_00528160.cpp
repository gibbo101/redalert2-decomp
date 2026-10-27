// bool IsometricTileClass::unknown_slot53(CoordStruct const *coord, int dir) (0x00528160)
// Places the tile at the coordinate and marks it mapped (slot 71).
#include "shared/isometric_tile.hpp"

bool IsometricTileClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    unknown_76 = false;
    unknown_slot103(*coord);
    return unknown_slot71(1);
}
