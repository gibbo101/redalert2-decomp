// bool __fastcall Unknown_0055AF80(int tile, int kind) (0x0055AF80)
// Whether a tile allows kind: every tile of the sets at 0x00A52E68 (40) and
// 0x00A6DD00 (20); of the four-tile sets at 0x00A52584, 0x00A6CF58,
// 0x00A52EA0 and 0x00A52EF0, the middle two always and the first and last
// unless kind is 0 or 4, 1 or 3, 0 or 1, 2 or 3 respectively.
#include "shared/map.hpp"
// @ref ?unknown_tileset_a52e68@@3HA=00a52e68
// @ref ?unknown_tileset_a52584@@3HA=00a52584
// @ref ?unknown_tileset_a6cf58@@3HA=00a6cf58
// @ref ?unknown_tileset_a52ea0@@3HA=00a52ea0
// @ref ?unknown_tileset_a52ef0@@3HA=00a52ef0
// @ref ?unknown_tileset_a6dd00@@3HA=00a6dd00

bool __fastcall Unknown_0055AF80(int tile, int kind)
{
    if (tile >= unknown_tileset_a52e68 && tile < unknown_tileset_a52e68 + 40) {
        return true;
    }
    if (tile >= unknown_tileset_a52584 && tile < unknown_tileset_a52584 + 4) {
        if (tile == unknown_tileset_a52584 || tile == unknown_tileset_a52584 + 3) {
            if (kind == 0 || kind == 4) {
                return false;
            }
            return true;
        }
    } else if (tile >= unknown_tileset_a6cf58 && tile < unknown_tileset_a6cf58 + 4) {
        if (tile == unknown_tileset_a6cf58 || tile == unknown_tileset_a6cf58 + 3) {
            if (kind == 1 || kind == 3) {
                return false;
            }
            return true;
        }
    } else if (tile >= unknown_tileset_a52ea0 && tile < unknown_tileset_a52ea0 + 4) {
        if (tile == unknown_tileset_a52ea0 || tile == unknown_tileset_a52ea0 + 3) {
            if (kind == 0 || kind == 1) {
                return false;
            }
            return true;
        }
    } else if (tile >= unknown_tileset_a52ef0 && tile < unknown_tileset_a52ef0 + 4) {
        if (tile == unknown_tileset_a52ef0 || tile == unknown_tileset_a52ef0 + 3) {
            if (kind == 2 || kind == 3) {
                return false;
            }
            return true;
        }
    } else if (tile < unknown_tileset_a6dd00 || tile >= unknown_tileset_a6dd00 + 20) {
        return false;
    }
    return true;
}
