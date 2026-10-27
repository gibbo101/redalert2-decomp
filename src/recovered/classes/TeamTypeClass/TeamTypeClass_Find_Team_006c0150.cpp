// TeamClass *TeamTypeClass::Find_Team() const (0x006C0150)
// The first team of this type, or null.
#include "shared/team_type.hpp"
#include "shared/team.hpp"

TeamClass *TeamTypeClass::Find_Team() const
{
    for (int index = 0; index < Teams.Count(); index++) {
        TeamClass *team = Teams[index];
        if (team->Class == this) {
            return team;
        }
    }
    return 0;
}
