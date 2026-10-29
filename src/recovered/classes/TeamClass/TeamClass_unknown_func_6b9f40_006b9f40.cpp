// bool TeamClass::unknown_func_6b9f40() (0x006B9F40; Red Alert's Coordinate_Regroup)
// Conscripts every member, then sends the live, initiated (or aircraft) members farther than the stray
// distance from the team's zone (+0x34) toward it (unless guarding with a target, mission 0x0B) and puts
// the near ones back to guard; returns whether none had to move, and then clears NeedsReGrouping.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848

bool TeamClass::unknown_func_6b9f40()
{
    FootClass *unit = Member;
    bool retval = true;
    while (unit != 0) {
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)) {
            if (unit->unknown_5d4c00(unknown_34) > Unknown_006BE6A0() && (unit->unknown_slot91() != 0xB || unit->unknown_228 == 0)) {
                if (unit->unknown_494 == 0) {
                    retval = false;
                    unit->unknown_slot116(2, false);
                    Cell dest = unit->unknown_4c8af0(Coord_Cell(unknown_34->Center_Coord()));
                    unit->unknown_slot260(&Map[dest], 1);
                }
            } else if (unit->unknown_slot91() != 0xB) {
                unit->unknown_slot116(5, false);
                unit->unknown_slot260(0, 1);
            }
        }
        unit = (FootClass *)unit->unknown_4c8;
    }
    if (retval == true) {
        NeedsReGrouping = false;
    }
    return retval;
}
