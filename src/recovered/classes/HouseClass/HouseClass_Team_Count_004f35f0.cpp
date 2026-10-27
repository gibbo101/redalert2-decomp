// int HouseClass::Team_Count(TeamTypeClass *team) (0x004F35F0)
// The number of teams of the house made from a team type (counted from the newest team back).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178

int HouseClass::Team_Count(TeamTypeClass *team)
{
    int count = 0;
    for (int index = Teams.Count() - 1; index >= 0; index--) {
        TeamClass *candidate = Teams[index];
        if (candidate != 0 && candidate->Owner == this && team == candidate->Class) {
            count++;
        }
    }
    return count;
}
