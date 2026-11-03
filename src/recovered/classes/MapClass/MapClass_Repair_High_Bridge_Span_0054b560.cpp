// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??0OverlayClass@@QAE@PAVOverlayTypeClass@@ABVCell@@H@Z=005da7d0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?Set_Bridge_End_State@MapClass@@QAEXABVCell@@_N1@Z=00550eb0
// @ref ?Set_Bridge_Middle_State@MapClass@@QAEXABVCell@@HHH_N@Z=005510a0
// @ref ?Unknown_0054EBD0@MapClass@@QAEHXZ=0054ebd0
// @ref ?Unknown_00550230@MapClass@@QAE_NABVCell@@@Z=00550230
// @ref ?Unknown_005688A0@MapClass@@QAEXAAV?$DynamicVectorClass@VCell@@@@@Z=005688a0
// @ref ?unknown_cell_a6f238@@3VCell@@A=00a6f238
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_tileset_a52c74@@3HA=00a52c74
// @ref ?unknown_tileset_a52c80@@3HA=00a52c80
// @ref ?unknown_tileset_a52e70@@3HA=00a52e70
// @ref ?unknown_tileset_a53390@@3HA=00a53390
// @ref ?unknown_tileset_a6cb7c@@3HA=00a6cb7c
// @ref ?unknown_tileset_a6e010@@3HA=00a6e010
// @ref ?unknown_tileset_a6e028@@3HA=00a6e028
// @ref _unknown_geometry_g=00a6fc30
// void MapClass::Repair_High_Bridge_Span_0054b560(CellClass *start, FacingType direction, Rect *dirty) (0x0054B560)
// TibSun MapClass::Repair_High_Bridge_Span: walks up to 30 cells from start toward direction (2 east-west,
// 4 north-south), repairs the middle pieces (Set_Bridge_Middle_State, subzone registration 0x00550230, a raised
// centre piece gets its three cells' heights back and its 2 x 5 cells queued) and stops at the far end piece
// (Set_Bridge_End_State). When an end was found the span is walked again laying the bridge overlay (OverlayTypes
// 24 / 25) on each repaired cell, the dirty rectangle spans both ends, and the zones / queued cells are
// recalculated. Draft by codex2 (86.96); the walks name the cell before Adjacent_Cell, and the dirty corner
// uses always.h min (two /Ob2 sites the original needs to call operator+ 0x0042ADD0 out of line).
#include "shared/dir_type.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_overlay.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/crt_memory.hpp"
#include "shared/always.hpp"
void *__cdecl operator new(unsigned int size);
extern int unknown_tileset_a6e028;
extern int unknown_tileset_a52c80;
extern int unknown_tileset_a6e010;
extern int unknown_tileset_a53390;

void MapClass::Repair_High_Bridge_Span_0054b560(CellClass *start, FacingType direction, Rect *dirty)
{
    Cell last = unknown_cell_a6f238;
    CellClass *cursor = &Map[start->Fetch_CellID()];
    bool zones_changed = false;
    DynamicVectorClass<Cell> changed;
    int length = 1;
    while (length < 30) {
        Cell id = cursor->Fetch_CellID();
        Cell next = Adjacent_Cell(id, direction);
        last = next;
        cursor = &Map[next];
        int tile = cursor->IsoTileIndex - unknown_tileset_a52c74 + 1;
        if (direction == 2) {
            if (tile == unknown_tileset_a6e028 && cursor->unknown_11a == 4) {
                Set_Bridge_End_State(last, false, false);
                zones_changed |= Unknown_00550230(Adjacent_Cell(last, 6));
                break;
            }
            if (tile == unknown_tileset_a52c80 && cursor->unknown_11a == 4) {
                Set_Bridge_End_State(last, false, false);
                zones_changed |= Unknown_00550230(Adjacent_Cell(last, 6));
                break;
            }
            if ((tile == unknown_tileset_a6cb7c || tile == unknown_tileset_a6cb7c + 3 ||
                 tile == unknown_tileset_a6cb7c + 4 || tile == unknown_tileset_a6cb7c + 1 ||
                 tile == unknown_tileset_a6cb7c + 2) && cursor->unknown_11a == 4) {
                Set_Bridge_Middle_State(last, unknown_tileset_a6cb7c - 1 + unknown_tileset_a52c74, -1, -1, false);
                zones_changed |= Unknown_00550230(last);
                if (tile == unknown_tileset_a6cb7c + 4) {
                    Map[last].unknown_11b += 4;
                    Map[Adjacent_Cell(last, 0)].unknown_11b += 4;
                    Map[Adjacent_Cell(last, 4)].unknown_11b += 4;
                    for (int x = 0; x < 2; ++x) {
                        for (int y = -2; y < 3; ++y) {
                            changed.Add(Cell(last + Cell(x, y)));
                        }
                    }
                }
            }
        } else if (direction == 4) {
            if (tile == unknown_tileset_a6e010 && cursor->unknown_11a == 2) {
                Set_Bridge_End_State(last, false, false);
                zones_changed |= Unknown_00550230(Adjacent_Cell(last, 0));
                break;
            }
            if (tile == unknown_tileset_a53390 && cursor->unknown_11a == 2) {
                Set_Bridge_End_State(last, false, false);
                zones_changed |= Unknown_00550230(Adjacent_Cell(last, 0));
                break;
            }
            if ((tile == unknown_tileset_a52e70 || tile == unknown_tileset_a52e70 + 3 ||
                 tile == unknown_tileset_a52e70 + 4 || tile == unknown_tileset_a52e70 + 2 ||
                 tile == unknown_tileset_a52e70 + 1) && cursor->unknown_11a == 2) {
                Set_Bridge_Middle_State(last, unknown_tileset_a52c74 - 1 + unknown_tileset_a52e70, -1, -1, false);
                zones_changed |= Unknown_00550230(last);
                if (tile == unknown_tileset_a52e70 + 4) {
                    Map[last].unknown_11b += 4;
                    Map[Adjacent_Cell(last, 2)].unknown_11b += 4;
                    Map[Adjacent_Cell(last, 6)].unknown_11b += 4;
                    for (int y = 0; y < 2; ++y) {
                        for (int x = -2; x < 3; ++x) {
                            changed.Add(Cell(last + Cell(x, y)));
                        }
                    }
                }
            }
        }
        ++length;
    }
    if (length == 30) return;
    cursor = &Map[start->Fetch_CellID()];
    if (dirty) {
        CoordStruct coord(start->Fetch_CellID(), unknown_geometry_g * start->unknown_11b);
        Point2D pixel;
        unknown_tactical_83996c->Coord_To_Pixel(coord, pixel);
        dirty->X = pixel.X;
        dirty->Y = pixel.Y;
    }
    if (length > 0) {
        int remaining = length;
        do {
            int tile = cursor->IsoTileIndex - unknown_tileset_a52c74 + 1;
            if ((tile != unknown_tileset_a6cb7c || (cursor->unknown_11a & 1)) &&
                (tile != unknown_tileset_a52e70 || (unsigned char)cursor->unknown_11a >= 5)) {
                if (direction == 2) new OverlayClass(OverlayTypes[24], cursor->Fetch_CellID(), -1);
                else new OverlayClass(OverlayTypes[25], cursor->Fetch_CellID(), -1);
            }
            Cell id = cursor->Fetch_CellID();
            Cell next = Adjacent_Cell(id, direction);
            last = next;
            cursor = &Map[next];
            --remaining;
        } while (remaining);
    }
    if (dirty) {
        CoordStruct coord(last, unknown_geometry_g * Map[last].unknown_11b);
        Point2D pixel;
        unknown_tactical_83996c->Coord_To_Pixel(coord, pixel);
        int original_x = dirty->X;
        int original_y = dirty->Y;
        dirty->X = min(dirty->X, pixel.X) - 64;
        dirty->Y = min(dirty->Y, pixel.Y) - 64;
        dirty->Width = abs(original_x - pixel.X) + 128;
        dirty->Height = abs(original_y - pixel.Y) + 128;
    }
    if (zones_changed) Unknown_0054EBD0();
    if (changed.Count() > 0) Unknown_005688A0(changed);
}
