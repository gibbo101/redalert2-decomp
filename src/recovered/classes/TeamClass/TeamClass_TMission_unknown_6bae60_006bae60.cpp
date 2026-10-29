// void TeamClass::TMission_unknown_6bae60(ScriptMissionClass const &mission, bool unknown) (0x006BAE60)
// When flagged, targets the cell of waypoint Data; unless the team is moving toward a following
// mission-3 line whose waypoint passes 0x0055A660, a cell the leader cannot enter is replaced by a
// reachable cell near it for the leader's speed type (none when there is none); then runs 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0
// @ref ?Has_Mission@ScriptClass@@QBE_NXZ=00668940
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?unknown_a40774@@3HA=00a40774
// @ref _unknown_geometry_k=00ac0050

void TeamClass::TMission_unknown_6bae60(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        FootClass *leader = unknown_func_6baa60();
        Cell cell = unknown_id_source_a3d290->Get_Waypoint_Location(mission.Data);
        unknown_func_6b79e0(&Map[cell]);
        bool adjust = true;
        if (IsMoving && Script->Has_Mission()) {
            ScriptMissionClass next = Script->Get_Current_Mission();
            if (next.Mission == 3 && !Map.Unknown_0055A660(unknown_id_source_a3d290->Get_Waypoint_Location(next.Data), true)) {
                adjust = false;
            }
        }
        if (adjust) {
            if (leader->unknown_slot101(&Map[cell], -1, -1, 0, 0) != 0) {
                cell = Map.Unknown_005502E0(cell, leader->unknown_slot32()->SpeedType, -1, 0, false,
                    Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            }
        }
        if (cell != unknown_geometry_k) {
            unknown_func_6b79e0(&Map[cell]);
        } else {
            unknown_func_6b79e0(0);
        }
    }
    unknown_func_6ba1a0();
}
