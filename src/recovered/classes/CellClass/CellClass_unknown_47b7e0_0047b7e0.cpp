// bool CellClass::unknown_47b7e0() const (0x0047B7E0): whether the cell's
// tile is in the 42-tile set at 0x00A6CB74 (unknown_47b7c0) or in one of the
// sets at 0x00A52580 (14), 0x00A52584, 0x00A6CF58, 0x00A52EA0 and 0x00A52EF0 (4).
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6cb74@@3HA=00a6cb74
// @ref ?unknown_tileset_a52580@@3HA=00a52580
// @ref ?unknown_tileset_a52584@@3HA=00a52584
// @ref ?unknown_tileset_a6cf58@@3HA=00a6cf58
// @ref ?unknown_tileset_a52ea0@@3HA=00a52ea0
// @ref ?unknown_tileset_a52ef0@@3HA=00a52ef0

bool CellClass::unknown_47b7e0() const
{
    if (IsoTileIndex >= unknown_tileset_a6cb74 && IsoTileIndex < unknown_tileset_a6cb74 + 42) {
        return true;
    }
    if ((IsoTileIndex < unknown_tileset_a52580 || IsoTileIndex >= unknown_tileset_a52580 + 14)
        && (IsoTileIndex < unknown_tileset_a52584 || IsoTileIndex >= unknown_tileset_a52584 + 4)
        && (IsoTileIndex < unknown_tileset_a6cf58 || IsoTileIndex >= unknown_tileset_a6cf58 + 4)
        && (IsoTileIndex < unknown_tileset_a52ea0 || IsoTileIndex >= unknown_tileset_a52ea0 + 4)
        && (IsoTileIndex < unknown_tileset_a52ef0 || IsoTileIndex >= unknown_tileset_a52ef0 + 4)) {
        return false;
    }
    return true;
}
