// bool CellClass::unknown_47b5b0() const (0x0047B5B0): whether the cell's
// tile is in the 20-tile set at 0x00A6E018 or the 12-tile set at 0x00A52EA8.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6e018@@3HA=00a6e018
// @ref ?unknown_tileset_a52ea8@@3HA=00a52ea8

bool CellClass::unknown_47b5b0() const
{
    if ((IsoTileIndex < unknown_tileset_a6e018 || IsoTileIndex >= unknown_tileset_a6e018 + 20) && (IsoTileIndex < unknown_tileset_a52ea8 || IsoTileIndex >= unknown_tileset_a52ea8 + 12)) {
        return false;
    }
    return true;
}
