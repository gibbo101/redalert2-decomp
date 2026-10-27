// void TeamClass::TMission_unknown_6bb020(ScriptMissionClass const &mission, bool unknown) (0x006BB020)
// When flagged targets the cell of waypoint Data (or the occupant of that cell); with a target, runs 0x006B9BB0 if any member has ammo to spare, otherwise clears the target and completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_6631a0@UnknownIDSource@@QAEPAVCellClass@@H@Z=006631a0
// @ref ?unknown_func_6b9bb0@TeamClass@@QAEXXZ=006b9bb0
// @ref ?unknown_471830@CellClass@@QAEPAVObjectClass@@ABUPoint2D@@_N@Z=00471830

void TeamClass::TMission_unknown_6bb020(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        CellClass *cell = unknown_id_source_a3d290->unknown_6631a0(mission.Data);
        if (cell != 0 && cell->Kind_Of() == 0xB) {
            ObjectClass *occupant = cell->unknown_471830(Point2D(0, 0), cell->unknown_140 >> 8 & 1);
            if (occupant != 0) {
                cell = (CellClass *)occupant;
            }
        }
        unknown_func_6b79e0(cell);
    }
    if (unknown_3c != 0) {
        for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
            if (member->unknown_slot32()->Ammo <= 0 || member->unknown_254 > 0) {
                unknown_func_6b9bb0();
                return;
            }
        }
    }
    unknown_func_6b79e0(0);
    StepCompleted = true;
}
