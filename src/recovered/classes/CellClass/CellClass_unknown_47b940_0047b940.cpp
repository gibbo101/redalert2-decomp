// bool CellClass::unknown_47b940() const (0x0047B940): whether the cell's tile
// is one of the 14 tiles of the set starting at 0x00A52C68.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52c68@@3HA=00a52c68

bool CellClass::unknown_47b940() const
{
    if (IsoTileIndex >= unknown_tileset_a52c68 && IsoTileIndex < unknown_tileset_a52c68 + 14) {
        return true;
    }
    return false;
}
