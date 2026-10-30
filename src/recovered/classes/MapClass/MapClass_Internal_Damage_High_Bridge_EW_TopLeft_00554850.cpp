// void MapClass::Internal_Damage_High_Bridge_EW_TopLeft(Cell const &cell, int dir) (0x00554850)
// The bridge cell next to a damaged one (TibSun name): a bridge deck cell's overlay
// frame moves to its damaged stage; an end tile (set offsets
// unknown_tileset_a6e0e4 / a52f80) is marked damaged (0x00550EB0) and a middle tile
// (unknown_tileset_a6cb7c + 0 / 1) takes its next stage (0x005510A0).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
// @ref ?unknown_tileset_a6e0e4@@3HA=00a6e0e4
// @ref ?unknown_tileset_a52f80@@3HA=00a52f80
// @ref ?Set_Bridge_End_State@MapClass@@QAEXABVCell@@_N1@Z=00550eb0
// @ref ?Set_Bridge_Middle_State@MapClass@@QAEXABVCell@@HHH_N@Z=005510a0

void MapClass::Internal_Damage_High_Bridge_EW_TopLeft(Cell const &cell, int dir)
{
    Cell adjacent = Adjacent_Cell(cell, dir);
    CellClass *adjacentptr = &Map[adjacent];
    if (adjacentptr->unknown_140 & 0x80) {
        if (adjacentptr->OverlayData > 3) {
            if (adjacentptr->OverlayData == 4) {
                adjacentptr->OverlayData = 6;
            }
        } else {
            adjacentptr->OverlayData = 5;
        }
    }
    int ittype = adjacentptr->IsoTileIndex - unknown_tileset_a52c74 + 1;
    if (ittype == unknown_tileset_a6e0e4 || ittype == unknown_tileset_a52f80) {
        Set_Bridge_End_State(adjacent, true, false);
    } else if (ittype == unknown_tileset_a6cb7c + 0) {
        Set_Bridge_Middle_State(adjacent, unknown_tileset_a52c74 + unknown_tileset_a6cb7c + 1, -1, -1, false);
    } else if (ittype == unknown_tileset_a6cb7c + 1) {
        Set_Bridge_Middle_State(adjacent, unknown_tileset_a52c74 + unknown_tileset_a6cb7c + 2, -1, -1, false);
    }
}
