// void MapClass::Internal_Destroy_Train_Bridge_NS_TopRight(Cell const &cell, int dir) (0x005521A0)
// TibSun Internal_Destroy_Train_Bridge_NS_TopRight: the piece of a north-south train bridge
// next to `cell` toward `dir` (Adjacent_Cell, whose TPoint2D<short> sum is called
// out of line here, 0x0042ADD0): a bridge deck cell's overlay drops a stage,
// its end piece (overlay data 17) is destroyed further along, cleared
// (0x00473700, overlay -1) and redrawn on the radar, another stage becomes (data 16); an end
// tile is marked damaged (0x00550EB0), a middle tile (set
// offset unknown_tileset_a52e70 + 0 / 1) takes stage 2, and a stage-3 middle
// tile is destroyed further along, its three bridge cells across the span dropped
// (0x00473000) and the tile set at stage 3 four levels lower.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
// @ref ?unknown_473000@CellClass@@QAEXXZ=00473000
// @ref ?unknown_473700@CellClass@@QAEXII@Z=00473700

void MapClass::Internal_Destroy_Train_Bridge_NS_TopRight(Cell const &cell, int dir)
{
    Cell adjacent = Adjacent_Cell(cell, dir);
    CellClass *adjacentptr = &Map[adjacent];
    if (adjacentptr->unknown_140 & 0x80) {
        if (adjacentptr->OverlayData >= 9) {
            if (adjacentptr->OverlayData > 15) {
                if (adjacentptr->OverlayData == 17) {
                    Internal_Destroy_Train_Bridge_NS_TopRight(adjacent, dir);
                    adjacentptr->unknown_473700(6, 0);
                    adjacentptr->OverlayData = 0;
                    adjacentptr->OverlayIndex = -1;
                    Map.Unknown_00631570(adjacentptr->MapCoords);
                }
            } else {
                adjacentptr->OverlayData = 16;
            }
        }
    }
    int ittype = adjacentptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
    if (ittype != unknown_tileset_a53394 && ittype != unknown_tileset_a52588) {
        if (ittype == unknown_tileset_a52e70 || ittype == unknown_tileset_a52e70 + 1) {
            Set_Bridge_Middle_State(adjacent, unknown_tileset_a6cb68 + unknown_tileset_a52e70 + 2, -1, -1, false);
        } else if (ittype == unknown_tileset_a52e70 + 3) {
            Internal_Destroy_Train_Bridge_NS_TopRight(adjacent, dir);
            if ((unsigned char)adjacentptr->unknown_11a > 4) {
                Map[adjacent + Cell(-1, -1)].unknown_473000();
                Map[adjacent + Cell(0, -1)].unknown_473000();
                Map[adjacent + Cell(1, -1)].unknown_473000();
                Set_Bridge_Middle_State(adjacent, unknown_tileset_a6cb68 + unknown_tileset_a52e70 + 3, -1, Map[adjacent + Cell(0, -1)].unknown_11b - 4, false);
            } else {
                Map[adjacent + Cell(-1, 0)].unknown_473000();
                Map[adjacent + Cell(0, 0)].unknown_473000();
                Map[adjacent + Cell(1, 0)].unknown_473000();
                Set_Bridge_Middle_State(adjacent, unknown_tileset_a6cb68 + unknown_tileset_a52e70 + 3, -1, Map[adjacent].unknown_11b - 4, false);
            }
        }
    } else {
        Set_Bridge_End_State(adjacent, true, false);
    }
}
