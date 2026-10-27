// bool CellClass::unknown_47b880() const (0x0047B880): whether the cell's tile
// is one of the 16 tiles of the set starting at 0x00A6E0E0.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6e0e0@@3HA=00a6e0e0

bool CellClass::unknown_47b880() const
{
    if (IsoTileIndex >= unknown_tileset_a6e0e0 && IsoTileIndex < unknown_tileset_a6e0e0 + 16) {
        return true;
    }
    return false;
}
