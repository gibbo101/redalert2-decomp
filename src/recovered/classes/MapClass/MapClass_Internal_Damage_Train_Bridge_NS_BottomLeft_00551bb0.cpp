// void MapClass::Internal_Damage_Train_Bridge_NS_BottomLeft(Cell const &cell, int dir) (0x00551BB0)
// The bridge cell next to a damaged one (TibSun name): a bridge deck cell's overlay
// frame moves to its damaged stage; an end tile (set offsets
// unknown_tileset_a6e010 / a53390) is marked damaged (0x00550EB0) and a middle tile
// (unknown_tileset_a52e70 + 0 / 2) takes its next stage (0x005510A0).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
// @ref ?Set_Bridge_End_State@MapClass@@QAEXABVCell@@_N1@Z=00550eb0
// @ref ?Set_Bridge_Middle_State@MapClass@@QAEXABVCell@@HHH_N@Z=005510a0

void MapClass::Internal_Damage_Train_Bridge_NS_BottomLeft(Cell const &cell, int dir)
{
    Cell adjacent = Adjacent_Cell(cell, dir);
    CellClass *adjacentptr = &Map[adjacent];
    if (adjacentptr->unknown_140 & 0x80) {
        if (adjacentptr->OverlayData >= 9) {
            if (adjacentptr->OverlayData > 0xC) {
                if (adjacentptr->OverlayData == 0xD) {
                    adjacentptr->OverlayData = 0xF;
                }
            } else {
                adjacentptr->OverlayData = 0xE;
            }
        }
    }
    int ittype = adjacentptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
    if (ittype == unknown_tileset_a6e010 || ittype == unknown_tileset_a53390) {
        Set_Bridge_End_State(adjacent, true, false);
    } else if (ittype == unknown_tileset_a52e70 + 0) {
        Set_Bridge_Middle_State(adjacent, unknown_tileset_a6cb68 + unknown_tileset_a52e70 + 0, -1, -1, false);
    } else if (ittype == unknown_tileset_a52e70 + 2) {
        Set_Bridge_Middle_State(adjacent, unknown_tileset_a6cb68 + unknown_tileset_a52e70 + 2, -1, -1, false);
    }
}
