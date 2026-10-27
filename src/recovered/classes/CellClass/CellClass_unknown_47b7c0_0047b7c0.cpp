// bool CellClass::unknown_47b7c0() const (0x0047B7C0): whether the cell's tile
// is one of the 42 tiles of the set starting at 0x00A6CB74.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6cb74@@3HA=00a6cb74

bool CellClass::unknown_47b7c0() const
{
    if (IsoTileIndex >= unknown_tileset_a6cb74 && IsoTileIndex < unknown_tileset_a6cb74 + 42) {
        return true;
    }
    return false;
}
