// void TeamClass::unknown_func_6b9bb0() (0x006B9BB0; Red Alert's Coordinate_Attack)
// Takes the mission target when the team has none; a cell target (unless the leader is an aircraft)
// becomes its occupant. Without a target completes the step; otherwise conscripts every member, sends
// infiltrating infantry on a mission-15 line to capture it (mission 8), puts the others to attack
// (mission 1) unless already attacking, entering, capturing, mission 17 or a busy mission 16, gives
// idle members the target, and completes the step when no member still can attack.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/infantry_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_471830@CellClass@@QAEPAVObjectClass@@ABUPoint2D@@_N@Z=00471830

void TeamClass::unknown_func_6b9bb0()
{
    if (unknown_40 == 0) {
        unknown_40 = unknown_3c;
    }
    if (unknown_40 != 0 && unknown_40->Kind_Of() == 0xB && Member != 0 && unknown_func_6baa60()->Kind_Of() != 2) {
        CellClass *cell = As_Cell(unknown_40);
        if (cell->unknown_471830(Point2D(0, 0), false) != 0) {
            unknown_40 = cell->unknown_471830(Point2D(0, 0), false);
        }
    }
    if (unknown_40 == 0) {
        StepCompleted = true;
        return;
    }
    ScriptMissionClass mission = Script->Get_Current_Mission();
    bool attacking = false;
    for (FootClass *unit = Member; unit != 0; unit = (FootClass *)unit->unknown_4c8) {
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)) {
            if (mission.Mission == 0xF && unit->Kind_Of() == 0xF && ((InfantryClass *)unit)->Type->Infiltrate) {
                unit->unknown_slot116(8, false);
                unit->unknown_slot220(unknown_40);
            } else if (unit->unknown_slot91() != 1 && unit->unknown_slot91() != 7 && unit->unknown_slot91() != 8
                && unit->unknown_slot91() != 0x11 && (unit->unknown_slot91() != 0x10 || !unit->unknown_slot284())) {
                unit->unknown_slot149(3);
                unit->unknown_slot116(1, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(0, 1);
            }
            if (unit->unknown_228 != unknown_40 && unit->unknown_228 == 0) {
                unit->unknown_slot220(unknown_40);
            }
            if (unit->Kind_Of() != 2 || unit->unknown_slot231(0)->WeaponType == 0 || unit->unknown_254 > 0) {
                attacking = true;
            }
        }
    }
    if (!attacking) {
        StepCompleted = true;
    }
}
