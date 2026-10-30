// bool DisplayClass::unknown_slot39(Cell const &cell, HouseClass *house) (0x0049A370, slot 39)
// The layer-0 form of slot 38 (hypothesis: Westwood's Map_Cell): marks the
// cell visible (+0x12C bit 3), takes its layer-0 shroud frame, then maps or
// refreshes the eight neighbours not fully shrouded (+0x12C bit 4) the same
// way. When the cell was newly visible or its frame changed, the map redraws
// it; that is also the result.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/abstract.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A8D40@Tactical@@QAEHABVCell@@H@Z=006a8d40
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0
// @ref ?Unknown_00568520@MapClass@@QAEXPAVCellClass@@PAVHouseClass@@_N@Z=00568520
// @ref ?unknown_slot39@DisplayClass@@UAE_NABVCell@@PAVHouseClass@@@Z=0049a370

bool DisplayClass::unknown_slot39(Cell const &cell, HouseClass *house)
{
    CellClass &target = (*this)[cell];
    bool changed = !(target.unknown_12c & 8);
    target.unknown_12c |= 8;
    bool shown = changed;
    unsigned char frame = unknown_tactical_83996c->Unknown_006A8D40(cell, 0);
    if (frame != target.unknown_120) {
        changed = true;
        target.unknown_120 = frame;
    }
    if (target.unknown_120 == 0xFF) {
        target.unknown_12c |= 0x10;
    }
    if (changed) {
        unknown_tactical_83996c->Unknown_006AADD0(&target);
    }
    for (int facing = 0; facing < 8; facing++) {
        Cell adjacent = AdjacentCell[facing & 7].unknown_42add0(cell);
        CellClass &next = (*this)[adjacent];
        if (adjacent == cell || (next.unknown_12c & 0x10)) {
            continue;
        }
        int next_frame = unknown_tactical_83996c->Unknown_006A8D40(adjacent, 0);
        if (next_frame == -1) {
            if (!(next.unknown_12c & 8)) {
                unknown_slot39(adjacent, house);
            } else {
                next.unknown_12c |= 0x10;
                unknown_tactical_83996c->Unknown_006AADD0(&next);
                for (int around = 0; around < 8; around++) {
                    Cell beyond = Adjacent_Cell(adjacent, around);
                    CellClass &far_cell = (*this)[beyond];
                    unsigned char far_frame = unknown_tactical_83996c->Unknown_006A8D40(beyond, 0);
                    if (far_frame != far_cell.unknown_120) {
                        far_cell.unknown_120 = far_frame;
                        unknown_tactical_83996c->Unknown_006AADD0(&far_cell);
                    }
                }
            }
        } else if (next_frame != -2 && !(next.unknown_12c & 8)) {
            unknown_slot39(adjacent, house);
        } else if (next_frame >= 0 && next_frame != (char)next.unknown_120) {
            next.unknown_120 = next_frame;
            unknown_tactical_83996c->Unknown_006AADD0(&next);
        }
    }
    if (changed) {
        Map.Unknown_00568520(&target, house, shown);
    }
    return changed;
}
