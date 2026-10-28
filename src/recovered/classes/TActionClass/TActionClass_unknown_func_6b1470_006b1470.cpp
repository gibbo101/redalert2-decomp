// bool TActionClass::unknown_func_6b1470(...) (0x006B1470)
// Reinforcements of the team type at +0x30 at its own waypoint; false without one.
#include "shared/taction.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/team_type.hpp"
// @ref ?Do_Reinforcements@@YI_NPAVTeamTypeClass@@H@Z=00639970

bool TActionClass::unknown_func_6b1470(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_30 != 0) {
        return Do_Reinforcements((TeamTypeClass *)unknown_30, -1);
    }
    return false;
}
