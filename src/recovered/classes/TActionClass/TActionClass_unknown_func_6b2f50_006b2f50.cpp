// bool TActionClass::unknown_func_6b2f50(...) (0x006B2F50)
// The first member of the team type's first team gets the talk bubble with Data.Value
// (TechnoClass 0x006D8FD0); without a team type it is cleared. Always true.
#include "shared/taction.hpp"
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/techno.hpp"

bool TActionClass::unknown_func_6b2f50(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_30 != 0) {
        TeamClass *team = ((TeamTypeClass *)unknown_30)->Find_Team();
        if (team != 0) {
            TechnoClass::unknown_6d8fd0(team->Member, Data.Value);
        }
    } else {
        TechnoClass::unknown_6d8fd0(0, 0);
    }
    return true;
}


