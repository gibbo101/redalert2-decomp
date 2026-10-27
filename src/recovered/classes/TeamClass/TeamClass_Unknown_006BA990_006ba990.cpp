// Whether the team is moving and its current script line is action 3 toward a waypoint that is not on the map.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Has_Mission@ScriptClass@@QBE_NXZ=00668940
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660

bool TeamClass::Unknown_006BA990()
{
    if (IsMoving && Script->Has_Mission()) {
        ScriptMissionClass mission = Script->Get_Current_Mission();
        if (mission.Mission == 3 && !Map.Unknown_0055A660(unknown_id_source_a3d290->Get_Waypoint_Location(mission.Data), true)) {
            return true;
        }
    }
    return false;
}
