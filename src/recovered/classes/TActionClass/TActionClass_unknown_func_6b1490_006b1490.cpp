// bool TActionClass::unknown_func_6b1490(...) (0x006B1490)
// Reinforcements of the team type at +0x30 at the waypoint +0x44; false without either.
#include "shared/taction.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/team_type.hpp"
// @ref ?Do_Reinforcements@@YI_NPAVTeamTypeClass@@H@Z=00639970

bool TActionClass::unknown_func_6b1490(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_30 != 0 && unknown_44 != -1) {
        return Do_Reinforcements((TeamTypeClass *)unknown_30, unknown_44);
    }
    return false;
}


