// bool CellClass::unknown_47b980() const (0x0047B980): whether the cell's tile
// is one of the 16 tiles of the set starting at 0x00A6CB68.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6cb68@@3HA=00a6cb68

bool CellClass::unknown_47b980() const
{
    if (IsoTileIndex >= unknown_tileset_a6cb68 && IsoTileIndex < unknown_tileset_a6cb68 + 16) {
        return true;
    }
    return false;
}
