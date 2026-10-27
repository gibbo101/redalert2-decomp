// bool CellClass::unknown_47b900() const (0x0047B900): whether the cell's tile
// is one of the 4 tiles of the set starting at 0x00A6DD08.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6dd08@@3HA=00a6dd08

bool CellClass::unknown_47b900() const
{
    if (IsoTileIndex >= unknown_tileset_a6dd08 && IsoTileIndex < unknown_tileset_a6dd08 + 4) {
        return true;
    }
    return false;
}
