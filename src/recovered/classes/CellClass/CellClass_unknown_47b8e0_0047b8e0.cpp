// bool CellClass::unknown_47b8e0() const (0x0047B8E0): whether the cell's tile
// is one of the 15 tiles of the set starting at 0x00A6DD0C.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6dd0c@@3HA=00a6dd0c

bool CellClass::unknown_47b8e0() const
{
    if (IsoTileIndex >= unknown_tileset_a6dd0c && IsoTileIndex < unknown_tileset_a6dd0c + 15) {
        return true;
    }
    return false;
}
