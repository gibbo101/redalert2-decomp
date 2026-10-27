// bool CellClass::unknown_47b860() const (0x0047B860): whether the cell's tile
// is one of the 14 tiles of the set starting at 0x00A52EF4.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52ef4@@3HA=00a52ef4

bool CellClass::unknown_47b860() const
{
    if (IsoTileIndex >= unknown_tileset_a52ef4 && IsoTileIndex < unknown_tileset_a52ef4 + 14) {
        return true;
    }
    return false;
}
