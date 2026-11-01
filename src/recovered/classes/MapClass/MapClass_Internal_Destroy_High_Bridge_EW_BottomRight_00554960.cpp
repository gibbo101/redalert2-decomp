// void MapClass::Internal_Destroy_High_Bridge_EW_BottomRight(Cell const &cell, int dir) (0x00554960)
// TibSun Internal_Destroy_High_Bridge_EW_BottomRight: the piece of an east-west high bridge
// next to `cell` toward `dir` (Adjacent_Cell, whose TPoint2D<short> sum is called
// out of line here, 0x0042ADD0): a bridge deck cell's overlay drops a stage,
// its end piece (overlay data 8) is destroyed further along, cleared
// (0x004732D0, overlay -1) and redrawn on the radar, another stage becomes (data 7); an end
// tile is marked damaged (0x00550EB0), a middle tile (set
// offset unknown_tileset_a6cb7c + 0 / 2) takes stage 2, and a stage-3 middle
// tile is destroyed further along, its three bridge cells across the span dropped
// (0x00473000) and the tile set at stage 3 four levels lower.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
// @ref ?unknown_473000@CellClass@@QAEXXZ=00473000
// @ref ?Set_Under_Bridge@CellClass@@QAEXI_N@Z=004732d0

void MapClass::Internal_Destroy_High_Bridge_EW_BottomRight(Cell const &cell, int dir)
{
    Cell adjacent = Adjacent_Cell(cell, dir);
    CellClass *adjacentptr = &Map[adjacent];
    if (adjacentptr->unknown_140 & 0x80) {
        if (adjacentptr->OverlayData > 6) {
            if (adjacentptr->OverlayData == 8) {
                Internal_Destroy_High_Bridge_EW_BottomRight(adjacent, dir);
                adjacentptr->Set_Under_Bridge(0, false);
                adjacentptr->OverlayData = 0;
                adjacentptr->OverlayIndex = -1;
                Map.Unknown_00631570(adjacentptr->MapCoords);
            }
        } else {
            adjacentptr->OverlayData = 7;
        }
    }
    int ittype = adjacentptr->IsoTileIndex - unknown_tileset_a52c74 + 1;
    if (ittype != unknown_tileset_a6e028 && ittype != unknown_tileset_a52c80) {
        if (ittype == unknown_tileset_a6cb7c || ittype == unknown_tileset_a6cb7c + 2) {
            Set_Bridge_Middle_State(adjacent, unknown_tileset_a52c74 + unknown_tileset_a6cb7c + 2, -1, -1, false);
        } else if (ittype == unknown_tileset_a6cb7c + 3) {
            Internal_Destroy_High_Bridge_EW_BottomRight(adjacent, dir);
            if ((adjacentptr->unknown_11a & 1) != 0) {
                Map[adjacent + Cell(-1, 0)].unknown_473000();
                Map[adjacent + Cell(-1, -1)].unknown_473000();
                Map[adjacent + Cell(-1, 1)].unknown_473000();
                Set_Bridge_Middle_State(adjacent, unknown_tileset_a52c74 + unknown_tileset_a6cb7c + 3, -1, Map[adjacent + Cell(-1, 0)].unknown_11b - 4, false);
            } else {
                Map[adjacent + Cell(0, 0)].unknown_473000();
                Map[adjacent + Cell(0, -1)].unknown_473000();
                Map[adjacent + Cell(0, 1)].unknown_473000();
                Set_Bridge_Middle_State(adjacent, unknown_tileset_a52c74 + unknown_tileset_a6cb7c + 3, -1, Map[adjacent].unknown_11b - 4, false);
            }
        }
    } else {
        Set_Bridge_End_State(adjacent, true, false);
    }
}
