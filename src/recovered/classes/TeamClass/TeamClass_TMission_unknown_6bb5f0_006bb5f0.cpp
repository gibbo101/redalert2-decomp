// void TeamClass::TMission_unknown_6bb5f0(ScriptMissionClass const &mission, bool unknown) (0x006BB5F0; Red Alert's TMission_Load)
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"

void TeamClass::TMission_unknown_6bb5f0(ScriptMissionClass const &mission, bool unknown)
{
    FootClass *unit = Member;
    FootClass *trans = 0;
    bool aircraft = unknown_func_6bd810();
    while (unit != 0) {
        if (unit->unknown_slot32()->Passengers > 0 && unit->Cargo.How_Many() < unit->unknown_slot32()->Passengers) {
            if ((!aircraft && unit->Kind_Of() == 1) || (aircraft && unit->Kind_Of() == 2)) {
                trans = unit;
                break;
            }
        }
        unit = (FootClass *)unit->unknown_4c8;
    }
    if (trans == 0) {
        StepCompleted = true;
        return;
    }
    if (trans->In_Radio_Contact()) {
        return;
    }
    bool finished = true;
    unit = Member;
    while (unit != 0 && unknown_48 > 1) {
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2) && unit != trans) {
            finished = false;
            if (unit->unknown_slot91() != 7) {
                unit->unknown_slot116(7, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(trans, 1);
                break;
            }
        }
        unit = (FootClass *)unit->unknown_4c8;
    }
    if (finished) {
        if (Class->TransportsReturnOnUnload) {
            CoordStruct coord = trans->Coord;
            trans->unknown_6d6e50(&Map[coord]);
        }
        StepCompleted = true;
    }
}
