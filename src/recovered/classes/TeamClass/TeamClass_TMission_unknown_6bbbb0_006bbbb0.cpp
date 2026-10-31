// void TeamClass::TMission_unknown_6bbbb0(ScriptMissionClass const &mission, bool unknown) (0x006BBBB0; Red Alert's Coordinate_Do)
// Conscripts every member; a live one without target and destination that strayed beyond twice the
// allowed distance (unless Data is mission 0xB) moves back to the team (+0x34), the cell beside it
// (0x004C8AF0) as destination; otherwise one without target and destination takes mission Data (except
// guard 5 over unloading 0x10).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"

void TeamClass::TMission_unknown_6bbbb0(ScriptMissionClass const &mission, bool unknown)
{
    FootClass *unit = Member;
    int do_mission = mission.Data;
    while (unit != 0) {
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)) {
            if (unit->unknown_228 == 0 && unit->unknown_494 == 0
                && unit->unknown_5d4c00(unknown_34) > Unknown_006BE6A0() * 2 && do_mission != 0xB) {
                unit->unknown_slot116(2, false);
                unit->unknown_slot260(unknown_34, 1);
                unit->unknown_slot116(2, false);
                Cell dest = unit->unknown_4c8af0(Coord_Cell(unknown_34->Center_Coord()));
                unit->unknown_slot260(&Map[dest], 1);
            } else if (unit->unknown_228 == 0 && unit->unknown_494 == 0 && unit->unknown_slot91() != do_mission
                && (do_mission != 5 || unit->unknown_slot91() != 0x10)) {
                unit->unknown_6d6e50(0);
                unit->unknown_slot116(do_mission, false);
                unit->unknown_slot220(0);
                unit->unknown_slot260(0, 1);
            }
        }
        unit = (FootClass *)unit->unknown_4c8;
    }
}
