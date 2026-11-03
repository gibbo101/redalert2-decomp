// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Destroy_Train_Bridge_Span_00553000@MapClass@@QAE_NABVCell@@W4FacingType@@PAVRect@@@Z=00553000
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_tileset_a52588@@3HA=00a52588
// @ref ?unknown_tileset_a52e70@@3HA=00a52e70
// @ref ?unknown_tileset_a52f80@@3HA=00a52f80
// @ref ?unknown_tileset_a53394@@3HA=00a53394
// @ref ?unknown_tileset_a6cb68@@3HA=00a6cb68
// @ref ?unknown_tileset_a6cb7c@@3HA=00a6cb7c
// @ref ?unknown_tileset_a6e0e4@@3HA=00a6e0e4
// @ref _unknown_empty_rect=00a6f228
// void MapClass::Destroy_Train_Bridge_Connections_00553570(Cell const &cell) (0x00553570)
// TibSun MapClass::Destroy_Train_Bridge_Connections: finds the first of the eight cells around `cell` that is
// (or was) under a bridge, takes the span's anchor from it (the deck cell of a live bridge, or two cells back
// from the end of a damaged one), then walks from the anchor toward the span start inside the map rectangle
// until an end or middle train-bridge piece is found and drops that span (0x00553000), registering the
// dirty area it reports.
#include "shared/dir_type.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/tactical.hpp"
#include "shared/shape_file.hpp"
extern int unknown_tileset_a6e0e4;
extern int unknown_tileset_a52f80;
extern int unknown_tileset_a53394;
extern int unknown_tileset_a52588;

void MapClass::Destroy_Train_Bridge_Connections_00553570(Cell const &cell)
{
    CellClass *cellptr = &unknown_dummy_cell_a6f9f8;
    int facing = FACING_N;
    for (int index = 0; index < 8; index++) {
        Cell adjacent = Adjacent_Cell(cell, facing);
        cellptr = &Map[adjacent];
        if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) {
            break;
        }
        facing = Facing_Add(facing, FACING_NE);
    }

    if (!cellptr->IsUnderBridge && !cellptr->WasUnderBridge) {
        return;
    }

    Cell origin;
    if (cellptr->IsUnderBridge) {
        origin = cellptr->Get_Bridge_Deck_Cell();
    } else {
        Cell walk = cellptr->Fetch_CellID();
        int count = 0;
        int step;
        if (cellptr->IsBridgeEastWest) {
            step = FACING_S;
        } else {
            step = FACING_E;
        }
        CellClass *walkptr;
        while (true) {
            Cell next = Adjacent_Cell(walk, step);
            walk = next;
            walkptr = &Map[next];
            if (walkptr->WasUnderBridge) {
                if (++count >= 4) {
                    return;
                }
            } else {
                break;
            }
        }
        FacingType back = Facing_Sub(step, FACING_S);
        origin = Adjacent_Cell(walk + AdjacentCell[back & 7], back);
    }

    int advance = cellptr->IsBridgeEastWest ? FACING_W : FACING_N;
    Rect dirty = unknown_empty_rect;
    Cell current = origin;

    while (current.X >= unknown_120) {
        if (current.X > unknown_120 + unknown_128) {
            return;
        }
        if (current.Y < unknown_124 || current.Y > unknown_124 + unknown_12c) {
            return;
        }

        int cellnum = current.X + current.Y * 512;
        if (Cells[cellnum] != 0) {
            CellClass *spanptr = &Map[current];
            int ittype = spanptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;

            if ((ittype == unknown_tileset_a6e0e4 || ittype == unknown_tileset_a52f80) && spanptr->unknown_11a == 8) {
                if (Destroy_Train_Bridge_Span_00553000(current, FACING_E, &dirty)) {
                    if (dirty != unknown_empty_rect) {
                        unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                    }
                }
                return;
            }

            if ((ittype == unknown_tileset_a6cb7c || ittype == unknown_tileset_a6cb7c + 3 ||
                 ittype == unknown_tileset_a6cb7c + 1 || ittype == unknown_tileset_a6cb7c + 2) &&
                spanptr->unknown_11a == 5) {
                if (Destroy_Train_Bridge_Span_00553000(current, FACING_E, &dirty)) {
                    if (dirty != unknown_empty_rect) {
                        unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                    }
                }
                return;
            }

            if ((ittype == unknown_tileset_a53394 || ittype == unknown_tileset_a52588) && spanptr->unknown_11a == 12) {
                if (Destroy_Train_Bridge_Span_00553000(current, FACING_S, &dirty)) {
                    if (dirty != unknown_empty_rect) {
                        unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                    }
                }
                return;
            }

            if ((ittype == unknown_tileset_a52e70 || ittype == unknown_tileset_a52e70 + 3 ||
                 ittype == unknown_tileset_a52e70 + 2 || ittype == unknown_tileset_a52e70 + 1) &&
                spanptr->unknown_11a == 7) {
                if (Destroy_Train_Bridge_Span_00553000(current, FACING_S, &dirty)) {
                    if (dirty != unknown_empty_rect) {
                        unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                    }
                }
                return;
            }
        }

        current = Adjacent_Cell(current, advance);
    }
}
