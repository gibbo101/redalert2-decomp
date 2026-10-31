// void TeamClass::TMission_unknown_6bd4b0(ScriptMissionClass const &mission, bool unknown) (0x006BD4B0; Red Alert's TMission_Unload)
// Members carrying passengers unload (mission 0x10) where their cell has no building; once none carries
// any, Data says who leaves the team: transports go home (with TransportsReturnOnUnload, to +0x1B0) or
// leave for Data 2 and 3, the others (non-transports, or units when the task force has a transport
// aircraft) leave for Data 1 and 3. Then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"

void TeamClass::TMission_unknown_6bd4b0(ScriptMissionClass const &mission, bool unknown)
{
    FootClass *unit = Member;
    bool finished = true;
    while (unit != 0) {
        FootClass *next = (FootClass *)unit->unknown_4c8;
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)) {
            if (unit->Cargo.Object != 0) {
                finished = false;
                if (Map[unit->Center_Coord()].unknown_4717b0() == 0 && unit->unknown_slot91() != 0x10) {
                    unit->unknown_slot260(0, 1);
                    unit->unknown_slot220(0);
                    unit->unknown_slot116(0x10, false);
                    finished = false;
                }
            }
        }
        unit = next;
    }
    if (!finished) {
        return;
    }
    unit = Member;
    int mode = mission.Data;
    bool aircraft = unknown_func_6bd810();
    while (unit != 0) {
        FootClass *next = (FootClass *)unit->unknown_4c8;
        if (unit->unknown_slot32()->Passengers == 0 || aircraft && unit->Kind_Of() != 2) {
            if (mode == 1 || mode == 3) {
                Unknown_006B8FB0(unit, -1, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(0, 1);
            }
        } else if (unit->unknown_slot32()->Passengers > 0) {
            if (Class->TransportsReturnOnUnload) {
                Unknown_006B8FB0(unit, -1, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(unit->unknown_1b0, 1);
                unit->unknown_slot116(2, false);
                if (unit->unknown_slot122()) {
                    unit->unknown_slot117();
                }
                unit->unknown_6d6e50(0);
            } else if (mode == 3 || mode == 2) {
                Unknown_006B8FB0(unit, -1, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(0, 1);
            }
        }
        unit = next;
    }
    StepCompleted = true;
}
