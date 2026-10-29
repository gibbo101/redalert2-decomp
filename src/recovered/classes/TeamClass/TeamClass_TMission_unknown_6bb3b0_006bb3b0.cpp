// void TeamClass::TMission_unknown_6bb3b0(ScriptMissionClass const &mission, int unknown) (0x006BB3B0)
// Moves every member into a new team of team type Data (same owner) and deletes this team.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_func_6b8cc0@TeamClass@@QAE_NPAVFootClass@@@Z=006b8cc0
// @ref ??0TeamClass@@QAE@PAVTeamTypeClass@@PAVHouseClass@@H@Z=006b7430
// @ref ??_GTeamClass@@UAEPAXI@Z=006be740
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48

void TeamClass::TMission_unknown_6bb3b0(ScriptMissionClass const &mission, int unknown)
{
    TeamClass *team = new TeamClass(TeamTypes[mission.Data], Owner, 0);
    FootClass *member = Member;
    while (member != 0) {
        Unknown_006B8FB0(member, -1, 0);
        team->unknown_func_6b8cc0(member);
        member = Member;
    }
    delete this;
}
