// void TeamTypeClass::Destroy_All_Of() const (0x006BED10)
// Deletes every team of this type.
#include "shared/team_type.hpp"
#include "shared/team.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178

void TeamTypeClass::Destroy_All_Of() const
{
    for (int index = 0; index < Teams.Count(); index++) {
        TeamClass *team = Teams[index];
        if (this == team->Class) {
            delete team;
            index--;
        }
    }
}
