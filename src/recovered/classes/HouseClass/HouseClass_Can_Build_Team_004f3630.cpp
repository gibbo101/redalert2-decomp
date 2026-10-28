// bool HouseClass::Can_Build_Team(TeamTypeClass *team) (0x004F3630)
// Whether the house can field every member type of the team's task force:
// each type must be buildable now (Who_Can_Build_Me); in the campaign a
// member type it cannot build is also accepted when one of the house's own
// foot objects of that type may join the team (0x006C0010).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/techno.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
// @ref ?unknown_func_6c0010@TeamTypeClass@@QAE_NPAVFootClass@@PAVHouseClass@@@Z=006c0010

bool HouseClass::Can_Build_Team(TeamTypeClass *team)
{
    if (team == 0 || team->TaskForce == 0) {
        return false;
    }
    for (int index = 0; index < team->TaskForce->CountEntries; index++) {
        TechnoTypeClass *type = team->TaskForce->Entries[index].Type;
        if (type == 0 || type->Who_Can_Build_Me(true, true, false, this) == 0) {
            if (unknown_game_mode_a3d298 != 0) {
                return false;
            }
            bool found = false;
            for (int foot_index = unknown_FootClass_list_00865f38.Count() - 1; foot_index >= 0; foot_index--) {
                FootClass *foot = unknown_FootClass_list_00865f38[foot_index];
                if (foot->House == this && type == foot->unknown_slot32() && team->unknown_func_6c0010(foot, this)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
    }
    return true;
}
