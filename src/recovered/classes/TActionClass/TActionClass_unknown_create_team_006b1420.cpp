// bool TActionClass::unknown_create_team(...) (0x006B1420)
// Creates one team of the team type at +0x30 with the global counter at 0x00A40774 raised around the call; always true.
#include "shared/taction.hpp"
#include "shared/team_type.hpp"
// @ref ?Create_One_Of@TeamTypeClass@@QAEPAVTeamClass@@PAVHouseClass@@@Z=006bec80
// @ref ?unknown_team_creating_a40774@@3HA=00a40774
extern int unknown_team_creating_a40774;

bool TActionClass::unknown_create_team(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_team_creating_a40774++;
    TeamTypeClass *team_type = (TeamTypeClass *)unknown_30;
    if (team_type != 0) {
        team_type->Create_One_Of(0);
    }
    unknown_team_creating_a40774--;
    return true;
}


