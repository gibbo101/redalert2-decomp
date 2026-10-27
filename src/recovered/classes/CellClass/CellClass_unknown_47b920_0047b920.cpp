// bool CellClass::unknown_47b920() const (0x0047B920): whether the cell's tile
// is one of the 4 tiles of the set starting at 0x00A52EE4.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52ee4@@3HA=00a52ee4

bool CellClass::unknown_47b920() const
{
    if (IsoTileIndex >= unknown_tileset_a52ee4 && IsoTileIndex < unknown_tileset_a52ee4 + 4) {
        return true;
    }
    return false;
}
