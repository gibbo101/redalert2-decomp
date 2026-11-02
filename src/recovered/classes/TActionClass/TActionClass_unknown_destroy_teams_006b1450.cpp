// bool TActionClass::unknown_destroy_teams(...) (0x006B1450)
// Destroys every team of the team type at +0x30; always true.
#include "shared/taction.hpp"
#include "shared/team_type.hpp"
// @ref ?Destroy_All_Of@TeamTypeClass@@QBEXXZ=006bed10

bool TActionClass::unknown_destroy_teams(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    TeamTypeClass *team_type = (TeamTypeClass *)unknown_30;
    if (team_type != 0) {
        team_type->Destroy_All_Of();
    }
    return true;
}


