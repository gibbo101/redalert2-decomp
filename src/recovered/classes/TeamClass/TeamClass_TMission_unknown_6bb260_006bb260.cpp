// void TeamClass::TMission_unknown_6bb260(ScriptMissionClass const &mission, bool unknown) (0x006BB260)
// When flagged targets the cell of waypoint Data; a cell target is replaced by the occupant at its centre (if any), then runs 0x006B9BB0 (or clears the target and completes the step when there is none).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_6631a0@UnknownIDSource@@QAEPAVCellClass@@H@Z=006631a0
// @ref ?unknown_func_6b9bb0@TeamClass@@QAEXXZ=006b9bb0
// @ref ?unknown_471830@CellClass@@QAEPAVObjectClass@@ABUPoint2D@@_N@Z=00471830

void TeamClass::TMission_unknown_6bb260(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        unknown_func_6b79e0(unknown_id_source_a3d290->unknown_6631a0(mission.Data));
    }
    if (unknown_3c != 0 && unknown_3c->Kind_Of() == 0xB) {
        CellClass *cell = As_Cell(unknown_3c);
        ObjectClass *occupant = cell->unknown_471830(Point2D(0, 0), false);
        if (occupant != 0) {
            unknown_func_6b79e0(occupant);
            unknown_func_6b9bb0();
        }
    } else {
        if (unknown_3c == 0) {
            unknown_func_6b79e0(0);
            StepCompleted = true;
        } else {
            unknown_func_6b9bb0();
        }
    }
}
