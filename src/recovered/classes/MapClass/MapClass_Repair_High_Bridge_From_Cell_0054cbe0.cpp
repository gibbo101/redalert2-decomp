// @ref ?Set_Bridge_End_State@MapClass@@QAEXABVCell@@_N1@Z=00550eb0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_tileset_a52c74@@3HA=00a52c74
// @ref ?unknown_tileset_a6cb7c@@3HA=00a6cb7c
// @ref ?unknown_tileset_a52e70@@3HA=00a52e70
// @ref ?unknown_tileset_a6e0e4@@3HA=00a6e0e4
// @ref ?unknown_tileset_a52f80@@3HA=00a52f80
// @ref ?unknown_tileset_a53394@@3HA=00a53394
// @ref ?unknown_tileset_a52588@@3HA=00a52588
// @ref ?Repair_High_Bridge_Span_0054b560@MapClass@@QAEXPAVCellClass@@W4FacingType@@PAVRect@@@Z=0054b560
// @ref ?Set_Bridge_Middle_State@MapClass@@QAEXABVCell@@HHH_N@Z=005510a0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
#include "shared/dir_type.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
extern int unknown_tileset_a52c74;
extern int unknown_tileset_a6cb7c;
extern int unknown_tileset_a52e70;
extern int unknown_tileset_a6e0e4;
extern int unknown_tileset_a52f80;
extern int unknown_tileset_a53394;
extern int unknown_tileset_a52588;

void MapClass::Repair_High_Bridge_From_Cell_0054cbe0(Cell const &origin)
{
    int radius = 1;
    for (;;) {
        int extent = unknown_128 > unknown_12c ? unknown_128 : unknown_12c;
        if (radius >= extent) return;
        for (int dy = -radius; dy < radius; ++dy) {
            for (int dx = -radius; dx < radius; ++dx) {
                Cell cell = origin + Cell(dx, dy);
                if (cell.X < unknown_120 || cell.X > unknown_120 + unknown_128 ||
                cell.Y < unknown_124 || cell.Y > unknown_124 + unknown_12c || !Has_Cell(cell)) continue;
                CellClass *piece = &Map[cell];
                int tile = piece->IsoTileIndex - unknown_tileset_a52c74 + 1;
                if ((tile == unknown_tileset_a6e0e4 || tile == unknown_tileset_a52f80) && piece->unknown_11a == 8) {
                    Set_Bridge_End_State(cell, false, false);
                    Repair_High_Bridge_Span_0054b560(piece, FACING_E, 0);
                    return;
                }
                if ((tile == unknown_tileset_a6cb7c || tile == unknown_tileset_a6cb7c + 3 ||
                tile == unknown_tileset_a6cb7c + 4 || tile == unknown_tileset_a6cb7c + 1 ||
                tile == unknown_tileset_a6cb7c + 2) && piece->unknown_11a == 5) {
                    if (tile == unknown_tileset_a6cb7c + 4) {
                        Set_Bridge_Middle_State(cell, unknown_tileset_a6cb7c - 1 + unknown_tileset_a52c74, -1, -1, false);
                        Cell const &base = Adjacent_Cell(cell, FACING_W);
                        Map[base].unknown_11b += 4;
                        Map[Adjacent_Cell(base, FACING_N)].unknown_11b += 4;
                        Map[Adjacent_Cell(base, FACING_S)].unknown_11b += 4;
                    }
                    Repair_High_Bridge_Span_0054b560(piece, FACING_E, 0);
                    return;
                }
                if ((tile == unknown_tileset_a53394 || tile == unknown_tileset_a52588) && piece->unknown_11a == 12) {
                    Set_Bridge_End_State(cell, false, false);
                    Repair_High_Bridge_Span_0054b560(piece, FACING_S, 0);
                    return;
                }
                if ((tile == unknown_tileset_a52e70 || tile == unknown_tileset_a52e70 + 3 ||
                tile == unknown_tileset_a52e70 + 4 || tile == unknown_tileset_a52e70 + 2 ||
                tile == unknown_tileset_a52e70 + 1) && piece->unknown_11a == 7) {
                    if (tile == unknown_tileset_a52e70 + 4) {
                        Set_Bridge_Middle_State(cell, unknown_tileset_a52e70 - 1 + unknown_tileset_a52c74, -1, -1, false);
                        Cell const &base = Adjacent_Cell(cell, FACING_N);
                        Map[base].unknown_11b += 4;
                        Map[Adjacent_Cell(base, FACING_E)].unknown_11b += 4;
                        Map[Adjacent_Cell(base, FACING_W)].unknown_11b += 4;
                    }
                    Repair_High_Bridge_Span_0054b560(piece, FACING_S, 0);
                    return;
                }
            }
        }
        ++radius;
    }
}
