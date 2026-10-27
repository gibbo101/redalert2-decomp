// bool DisplayClass::unknown_slot37(Cell const &cell, int arg2, bool arg3) (0x00499FC0, slot 37)
// Maps a cell (hypothesis: Westwood's Map_Cell): marks it mapped (+0x140 bit
// 1, bit 6 cleared), counts the viewer in or out (arg3), takes the tactical
// view's shroud frames of both layers, and when anything changed has the
// view and the map redraw it. True when it changed.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/abstract.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A8D40@Tactical@@QAEHABVCell@@H@Z=006a8d40
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0
// @ref ?Unknown_00568520@MapClass@@QAEXPAVCellClass@@H_N@Z=00568520
// @ref ?unknown_47be00@CellClass@@QAEXXZ=0047be00
// @ref ?unknown_47c840@CellClass@@QAEXXZ=0047c840
// @ref ?unknown_47c8a0@CellClass@@QAEXXZ=0047c8a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool DisplayClass::unknown_slot37(Cell const &cell, int arg2, bool arg3)
{
    CellClass &target = (*this)[cell];
    bool unmapped = !(target.unknown_140 & 2);
    bool changed = !(target.unknown_140 & 2) || !(target.unknown_12c & 8);
    bool mapped = changed;
    target.unknown_140 = (target.unknown_140 & ~0x40) | 2;
    if (arg3) {
        target.unknown_47c8a0();
    } else {
        target.unknown_47c840();
    }
    unsigned char frame = unknown_tactical_83996c->Unknown_006A8D40(cell, 0);
    if (frame != target.unknown_120) {
        changed = true;
        target.unknown_120 = frame;
    }
    if (target.unknown_120 == 0xFF) {
        target.unknown_12c |= 0x10;
    }
    frame = unknown_tactical_83996c->Unknown_006A8D40(cell, 1);
    if (frame != target.unknown_121) {
        changed = true;
        target.unknown_121 = frame;
    }
    if (target.unknown_121 == 0xFF) {
        target.unknown_140 |= 1;
    }
    if (changed) {
        unknown_tactical_83996c->Unknown_006AADD0(&target);
        Map.Unknown_00568520(&target, arg2, mapped);
    }
    if ((target.unknown_140 & 2) && unmapped && (unknown_id_source_a3d290->unknown_000 & 0x1000)) {
        target.unknown_47be00();
    }
    return changed;
}
