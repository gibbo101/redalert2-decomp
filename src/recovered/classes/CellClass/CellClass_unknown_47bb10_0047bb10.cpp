// bool CellClass::unknown_47bb10() const (0x0047BB10): whether the cell's
// tile is the one at 0x00A6E0F8 or the next.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6e0f8@@3HA=00a6e0f8

bool CellClass::unknown_47bb10() const
{
    if (IsoTileIndex == unknown_tileset_a6e0f8) {
        return true;
    }
    return IsoTileIndex == unknown_tileset_a6e0f8 + 1 ? true : false;
}
