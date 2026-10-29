// Disbands every team of the house whose team type has a lower priority than the given one: removes its members, flags it to disappear and starts its leaving timer.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref __ftol=0077f110
// @ref ?Frame@@3HA=00a40d2c

void __fastcall TeamClass::unknown_func_6ba8e0(int priority, HouseClass *house)
{
    for (int index = 0; index < Teams.Count(); index++) {
        TeamClass *team = Teams[index];
        if (team != 0 && house == team->Owner && team->Class->Priority < priority) {
            while (team->Member != 0) {
                team->Unknown_006B8FB0(team->Member, -1, 0);
            }
            team->JustDisappeared = true;
            team->NeedsToDisappear = true;
            team->unknown_64 = UnknownTimer423F60((long)(Rules->unknown_1150 * 900.0));
            team->IsLeavingMap = true;
        }
    }
}
