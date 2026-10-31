// bool CellClass::unknown_47b5e0() const (0x0047B5E0): Westwood's Is_Tile_Cliff. The tile is in
// one of the cliff sets: cliffs, the four waterfall sets (except the two end tiles' open
// subtiles), cliff ramps, water caves, bridges, train bridges, destroyable and water cliffs.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52e64@@3HA=00a52e64
// @ref ?unknown_tileset_a6cb70@@3HA=00a6cb70

bool CellClass::unknown_47b5e0() const
{
    if (unknown_tileset_a52e68 != -1 && IsoTileIndex >= unknown_tileset_a52e68 && IsoTileIndex < unknown_tileset_a52e68 + 40) {
        return true;
    }
    if (unknown_tileset_a52584 != -1 && IsoTileIndex >= unknown_tileset_a52584 && IsoTileIndex < unknown_tileset_a52584 + 4) {
        if (IsoTileIndex == unknown_tileset_a52584 || IsoTileIndex == unknown_tileset_a52584 + 3) {
            if (unknown_11a == 0 || unknown_11a == 4) {
                return false;
            }
        }
        return true;
    }
    if (unknown_tileset_a6cf58 != -1 && IsoTileIndex >= unknown_tileset_a6cf58 && IsoTileIndex < unknown_tileset_a6cf58 + 4) {
        if (IsoTileIndex == unknown_tileset_a6cf58 || IsoTileIndex == unknown_tileset_a6cf58 + 3) {
            if (unknown_11a == 1 || unknown_11a == 3) {
                return false;
            }
        }
        return true;
    }
    if (unknown_tileset_a52ea0 != -1 && IsoTileIndex >= unknown_tileset_a52ea0 && IsoTileIndex < unknown_tileset_a52ea0 + 4) {
        if (IsoTileIndex == unknown_tileset_a52ea0 || IsoTileIndex == unknown_tileset_a52ea0 + 3) {
            if (unknown_11a == 0 || unknown_11a == 1) {
                return false;
            }
        }
        return true;
    }
    if (unknown_tileset_a52ef0 != -1 && IsoTileIndex >= unknown_tileset_a52ef0 && IsoTileIndex < unknown_tileset_a52ef0 + 4) {
        if (IsoTileIndex == unknown_tileset_a52ef0 || IsoTileIndex == unknown_tileset_a52ef0 + 3) {
            if (unknown_11a == 2 || unknown_11a == 3) {
                return false;
            }
        }
        return true;
    }
    if (unknown_tileset_a6dd00 != -1 && IsoTileIndex >= unknown_tileset_a6dd00 && IsoTileIndex < unknown_tileset_a6dd00 + 20) {
        return true;
    }
    if (unknown_tileset_a6cb70 != -1 && IsoTileIndex >= unknown_tileset_a6cb70 && IsoTileIndex < unknown_tileset_a6cb70 + 4) {
        return true;
    }
    if (unknown_tileset_a52c74 != -1 && IsoTileIndex >= unknown_tileset_a52c74 && IsoTileIndex < unknown_tileset_a52c74 + 16) {
        return true;
    }
    if (unknown_tileset_a6cb68 != -1 && IsoTileIndex >= unknown_tileset_a6cb68 && IsoTileIndex < unknown_tileset_a6cb68 + 16) {
        return true;
    }
    if (unknown_tileset_a6e0f8 != -1 && IsoTileIndex >= unknown_tileset_a6e0f8 && IsoTileIndex < unknown_tileset_a6e0f8 + 2) {
        return true;
    }
    if (unknown_tileset_a52e64 != -1 && IsoTileIndex >= unknown_tileset_a52e64 && IsoTileIndex < unknown_tileset_a52e64 + 28) {
        return true;
    }
    return false;
}
