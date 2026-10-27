// bool CellClass::unknown_47b960() const (0x0047B960): whether the cell's tile
// is one of the 16 tiles of the set starting at 0x00A52C74.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52c74@@3HA=00a52c74

bool CellClass::unknown_47b960() const
{
    if (IsoTileIndex >= unknown_tileset_a52c74 && IsoTileIndex < unknown_tileset_a52c74 + 16) {
        return true;
    }
    return false;
}
