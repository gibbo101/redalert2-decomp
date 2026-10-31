// bool DisplayClass::unknown_slot38(Cell const &cell, HouseClass *house) (0x0049A0F0, slot 38)
// Maps a cell for the tactical view's layer 1 (hypothesis: Westwood's
// Map_Cell for the second shroud layer): marks it mapped, takes its layer-1
// shroud frame, then looks at the eight neighbours that are not fully
// shrouded: a neighbour the view reports fully shrouded (-1) is mapped in
// turn when it is still unmapped, else is marked fully shrouded and its own
// neighbours refreshed; other unmapped neighbours (not -2) are mapped; mapped
// ones take their new frame. When the cell was newly mapped the map redraws
// it. True when it was newly mapped or its frame changed.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/abstract.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Cell_Shadow@Tactical@@QAEHABVCell@@_N@Z=006a8d40
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0
// @ref ?Unknown_00568520@MapClass@@QAEXPAVCellClass@@PAVHouseClass@@_N@Z=00568520
// @ref ?unknown_47be00@CellClass@@QAEXXZ=0047be00
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool DisplayClass::unknown_slot38(Cell const &cell, HouseClass *house)
{
    CellClass &target = (*this)[cell];
    char unmapped = !(target.unknown_140 & 2);
    bool changed = !(target.unknown_140 & 2);
    bool mapped = changed;
    target.unknown_140 = (target.unknown_140 & ~0x40) | 2;
    unsigned char frame = unknown_tactical_83996c->Cell_Shadow(cell, 1);
    if (frame != target.unknown_121) {
        changed = true;
        target.unknown_121 = frame;
    }
    if (target.unknown_121 == 0xFF) {
        target.unknown_140 |= 1;
    }
    if (changed) {
        unknown_tactical_83996c->Unknown_006AADD0(&target);
    }
    for (int facing = 0; facing < 8; facing++) {
        Cell adjacent = Adjacent_Cell(cell, facing);
        CellClass &next = (*this)[adjacent];
        if (adjacent == cell || (next.unknown_140 & 1)) {
            continue;
        }
        int next_frame = unknown_tactical_83996c->Cell_Shadow(adjacent, 1);
        if (next_frame == -1) {
            if (!(next.unknown_140 & 2)) {
                unknown_slot38(adjacent, house);
            } else {
                next.unknown_140 |= 1;
                unknown_tactical_83996c->Unknown_006AADD0(&next);
                for (int around = 0; around < 8; around++) {
                    Cell beyond = Adjacent_Cell(adjacent, around);
                    CellClass &far_cell = (*this)[beyond];
                    unsigned char far_frame = unknown_tactical_83996c->Cell_Shadow(beyond, 1);
                    if (far_frame != far_cell.unknown_121) {
                        far_cell.unknown_121 = far_frame;
                        unknown_tactical_83996c->Unknown_006AADD0(&far_cell);
                    }
                }
            }
        } else if (next_frame != -2 && !(next.unknown_140 & 2)) {
            unknown_slot38(adjacent, house);
        } else if (next_frame >= 0 && next_frame != (char)next.unknown_121) {
            next.unknown_121 = next_frame;
            unknown_tactical_83996c->Unknown_006AADD0(&next);
        }
    }
    if (changed) {
        Map.Unknown_00568520(&target, house, mapped);
    }
    if ((target.unknown_140 & 2) && unmapped && (unknown_id_source_a3d290->unknown_000 & 0x1000)) {
        target.unknown_47be00();
    }
    return changed;
}
