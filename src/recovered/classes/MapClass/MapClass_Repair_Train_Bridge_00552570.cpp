// void MapClass::Unknown_00552570(Cell const &cell) (0x00552570)
// TibSun MapClass::Repair_Train_Bridge: a low bridge in the 5 x 5 block around the cell is repaired as a low
// span (0x00561100); otherwise the nearest bridge cell (the cell itself, else up to three cells out along each
// of the eight facings) gives the span start (its deck cell, or for a destroyed span the cell two steps back
// from the end of the run of was-under-bridge cells), and the span is walked repairing its end or middle
// pieces (Set_Bridge_End_State / Set_Bridge_Middle_State, Repair_Train_Bridge_Span 0x0054BE80 and the
// tactical dirty area; a raised centre piece gets its heights back, its subzones registered and its 2 x 5
// cells queued, then the neighbouring span is repaired recursively). Draft started from codex2's (45.68).
// The step back to the span start is one inline sum and one Adjacent_Cell (the original expands the first
// step's operator+ and calls the second; hypothesis for the source form).
// @ref ?Unknown_00552570@MapClass@@QAEXABVCell@@@Z=00552570
// @ref ?Repair_Train_Bridge_Span_0054be80@MapClass@@QAEXPAVCellClass@@W4FacingType@@PAVRect@@@Z=0054be80
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Set_Bridge_End_State@MapClass@@QAEXABVCell@@_N1@Z=00550eb0
// @ref ?Set_Bridge_Middle_State@MapClass@@QAEXABVCell@@HHH_N@Z=005510a0
// @ref ?Unknown_0054EBD0@MapClass@@QAEHXZ=0054ebd0
// @ref ?Unknown_00550230@MapClass@@QAE_NABVCell@@@Z=00550230
// @ref ?Unknown_005688A0@MapClass@@QAEXAAV?$DynamicVectorClass@VCell@@@@@Z=005688a0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_tileset_a6cb68@@3HA=00a6cb68
// @ref ?unknown_tileset_a6cb7c@@3HA=00a6cb7c
// @ref ?unknown_tileset_a52e70@@3HA=00a52e70
// @ref ?unknown_tileset_a6e0e4@@3HA=00a6e0e4
// @ref ?unknown_tileset_a52f80@@3HA=00a52f80
// @ref ?unknown_tileset_a53394@@3HA=00a53394
// @ref ?unknown_tileset_a52588@@3HA=00a52588
#include "shared/dir_type.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/tactical.hpp"
extern int unknown_tileset_a6e0e4;
extern int unknown_tileset_a52f80;
extern int unknown_tileset_a53394;
extern int unknown_tileset_a52588;

void MapClass::Unknown_00552570(Cell const &cell)
{
    for (int x = -2; x < 3; x++) {
        for (int y = -2; y < 3; y++) {
            if (Unknown_00562930(cell + Cell(x, y))) {
                Repair_Low_Bridge_Span(cell + Cell(x, y));
                return;
            }
        }
    }

    CellClass *cellptr = &Map[cell];
    int facing = FACING_N;
    if (!cellptr->IsUnderBridge && !cellptr->WasUnderBridge) {
        for (int index = 0; index < 8; index++) {
            Cell adjacent = Adjacent_Cell(cell, Facing_Add(facing, FACING_N));
            cellptr = &Map[adjacent];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) {
                break;
            }
            adjacent = Adjacent_Cell(adjacent, Facing_Add(facing, FACING_N));
            cellptr = &Map[adjacent];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) {
                break;
            }
            adjacent = Adjacent_Cell(adjacent, Facing_Add(facing, FACING_N));
            cellptr = &Map[adjacent];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) {
                break;
            }
            facing = Facing_Add(facing, FACING_NE);
        }
    }

    if (!cellptr->IsUnderBridge && !cellptr->WasUnderBridge) {
        return;
    }

    Cell origin;
    if (cellptr->IsUnderBridge) {
        origin = cellptr->Get_Bridge_Deck_Cell();
    } else {
        int count = 0;
        int step = cellptr->IsBridgeEastWest ? FACING_S : FACING_E;
        origin = cellptr->Fetch_CellID();
        CellClass *walkptr;
        while (true) {
            origin = Adjacent_Cell(origin, Facing_Add(step, FACING_N));
            walkptr = &Map[origin];
            if (walkptr->WasUnderBridge) {
                if (++count >= 4) {
                    return;
                }
            } else {
                break;
            }
        }
        FacingType back = Facing_Sub(step, FACING_S);
        origin = Adjacent_Cell(origin + AdjacentCell[back & 7], back);
    }

    int advance = cellptr->IsBridgeEastWest ? FACING_W : FACING_N;
    Cell spancell = origin;
    char zonechanged = 0;
    int ittype = 0;
    DynamicVectorClass<Cell> cells;
    Rect dirty;
    while (true) {
        if (!Map.Unknown_0054AAB0(spancell)) {
            break;
        }
        if (Cells[spancell.X + spancell.Y * 512] != 0) {
            CellClass *spanptr = &Map[spancell];
            ittype = spanptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
            if ((ittype == unknown_tileset_a6e0e4 || ittype == unknown_tileset_a52f80) && spanptr->unknown_11a == 8) {
                Set_Bridge_End_State(spancell, false, false);
                Repair_Train_Bridge_Span_0054be80(&Map[spancell], FACING_E, &dirty);
                unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                break;
            }
            if ((ittype == unknown_tileset_a6cb7c || ittype == unknown_tileset_a6cb7c + 3 ||
                 ittype == unknown_tileset_a6cb7c + 4 || ittype == unknown_tileset_a6cb7c + 1 ||
                 ittype == unknown_tileset_a6cb7c + 2) && spanptr->unknown_11a == 5) {
                if (ittype == unknown_tileset_a6cb7c + 4) {
                    Set_Bridge_Middle_State(spancell, unknown_tileset_a6cb7c + unknown_tileset_a6cb68 - 1, -1, -1, false);
                    Cell middle = Adjacent_Cell(spancell, FACING_W);
                    Map[middle].unknown_11b += 4;
                    Map[Adjacent_Cell(middle, FACING_N)].unknown_11b += 4;
                    Map[Adjacent_Cell(middle, FACING_S)].unknown_11b += 4;
                    zonechanged = Unknown_00550230(middle);
                    for (int dx = 0; dx < 2; dx++) {
                        for (int dy = -2; dy < 3; dy++) {
                            cells.Add(Cell(middle + Cell(dx, dy)));
                        }
                    }
                }
                Unknown_00552570(spancell + Cell(-2, 0));
                Repair_Train_Bridge_Span_0054be80(&Map[spancell], FACING_E, &dirty);
                unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                break;
            }
            if ((ittype == unknown_tileset_a53394 || ittype == unknown_tileset_a52588) && spanptr->unknown_11a == 12) {
                Set_Bridge_End_State(spancell, false, false);
                Repair_Train_Bridge_Span_0054be80(&Map[spancell], FACING_S, &dirty);
                unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                break;
            }
            if ((ittype == unknown_tileset_a52e70 || ittype == unknown_tileset_a52e70 + 3 ||
                 ittype == unknown_tileset_a52e70 + 4 || ittype == unknown_tileset_a52e70 + 1 ||
                 ittype == unknown_tileset_a52e70 + 2) && spanptr->unknown_11a == 7) {
                if (ittype == unknown_tileset_a52e70 + 4) {
                    Set_Bridge_Middle_State(spancell, unknown_tileset_a52e70 + unknown_tileset_a6cb68 - 1, -1, -1, false);
                    Cell middle = Adjacent_Cell(spancell, FACING_N);
                    Map[middle].unknown_11b += 4;
                    Map[Adjacent_Cell(middle, FACING_E)].unknown_11b += 4;
                    Map[Adjacent_Cell(middle, FACING_W)].unknown_11b += 4;
                    zonechanged = Unknown_00550230(middle);
                    for (int dy = 0; dy < 2; dy++) {
                        for (int dx = -2; dx < 3; dx++) {
                            cells.Add(Cell(middle + Cell(dx, dy)));
                        }
                    }
                }
                Unknown_00552570(spancell + Cell(0, -2));
                Repair_Train_Bridge_Span_0054be80(&Map[spancell], FACING_S, &dirty);
                unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
                break;
            }
        }
        spancell = Adjacent_Cell(spancell, Facing_Add(advance, FACING_N));
    }

    if (zonechanged) {
        Unknown_0054EBD0();
    }
    if (cells.Count() > 0) {
        Unknown_005688A0(cells);
    }
}
