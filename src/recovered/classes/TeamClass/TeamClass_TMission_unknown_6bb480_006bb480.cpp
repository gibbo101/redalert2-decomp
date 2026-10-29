// void TeamClass::TMission_unknown_6bb480(ScriptMissionClass const &mission, int unknown) (0x006BB480)
// Sends the team's leader to a target found from Data, then completes the
// step once every member has ammo.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
// @ref ?Unknown_006220E0@@YIHH@Z=006220e0
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6b9bb0@TeamClass@@QAEXXZ=006b9bb0
// @ref ?unknown_a40774@@3HA=00a40774

// Whether the team may complete the step: no member is out of ammo.
inline bool Team_Members_Armed(TeamClass *team)
{
    if (team->unknown_3c != 0) {
        for (FootClass *member = team->Member; member != 0; member = (FootClass *)member->unknown_4c8) {
            if (member->unknown_slot32()->Ammo <= 0 || member->unknown_254 > 0) {
                return false;
            }
        }
    }
    return true;
}

void TeamClass::TMission_unknown_6bb480(ScriptMissionClass const &mission, int unknown)
{
    if (unknown_3c == 0 && Member != 0) {
        FootClass *leader = unknown_func_6baa60();
        int target_data = Unknown_006220E0(mission.Data);
        AbstractClass *target = leader->unknown_slot219(target_data, &CoordStruct(leader->Coord), Class->OnlyTargetHouseEnemy);
        unknown_func_6b79e0(target);
        if (Team_Members_Armed(this)) {
            StepCompleted = true;
        }
    }
    if (Team_Members_Armed(this)) {
        StepCompleted = true;
    }
    unknown_func_6b9bb0();
}

