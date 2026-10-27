// bool CellClass::unknown_47b9a0() const (0x0047B9A0): whether the cell's tile
// is one of the 16 tiles of the set starting at 0x00A52C70.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52c70@@3HA=00a52c70

bool CellClass::unknown_47b9a0() const
{
    if (IsoTileIndex >= unknown_tileset_a52c70 && IsoTileIndex < unknown_tileset_a52c70 + 16) {
        return true;
    }
    return false;
}
