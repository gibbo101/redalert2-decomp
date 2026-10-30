// bool __fastcall Unknown_00556B30(int tile, int kind, CellClass const *cell) (0x00556B30)
// Whether a tile is a bridge piece of direction kind 2 or 4 (one tile of two
// sets, or one of four consecutive tiles of a third) on a cell whose +0x11A
// is the other kind (4 for kind 2, 2 for kind 4) (called by 0x00556520 and 0x00557090; name hypothesis).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_tileset_a6e028@@3HA=00a6e028
// @ref ?unknown_tileset_a52c80@@3HA=00a52c80
// @ref ?unknown_tileset_a6cb7c@@3HA=00a6cb7c
// @ref ?unknown_tileset_a6e010@@3HA=00a6e010
// @ref ?unknown_tileset_a53390@@3HA=00a53390
// @ref ?unknown_tileset_a52e70@@3HA=00a52e70

bool __fastcall Unknown_00556B30(int tile, int kind, CellClass const *cell)
{
    if (kind == 2) {
        if (tile == unknown_tileset_a6e028 && cell->unknown_11a == 4) {
            return true;
        }
        if (tile == unknown_tileset_a52c80 && cell->unknown_11a == 4) {
            return true;
        }
        if ((tile == unknown_tileset_a6cb7c || tile == unknown_tileset_a6cb7c + 3
                || tile == unknown_tileset_a6cb7c + 1 || tile == unknown_tileset_a6cb7c + 2)
                && cell->unknown_11a == 4) {
            return true;
        }
    } else if (kind == 4) {
        if (tile == unknown_tileset_a6e010 && cell->unknown_11a == 2) {
            return true;
        }
        if (tile == unknown_tileset_a53390 && cell->unknown_11a == 2) {
            return true;
        }
        if ((tile == unknown_tileset_a52e70 || tile == unknown_tileset_a52e70 + 3
                || tile == unknown_tileset_a52e70 + 1 || tile == unknown_tileset_a52e70 + 2)
                && cell->unknown_11a == 2) {
            return true;
        }
    }
    return false;
}
