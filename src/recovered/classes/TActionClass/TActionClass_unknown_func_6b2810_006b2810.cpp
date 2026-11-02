// bool TActionClass::unknown_func_6b2810(...) (0x006B2810)
// Unknown_0063A880 with the team type at +0x30 and the waypoint +0x44; false without either.
#include "shared/taction.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/team_type.hpp"
// @ref ?Unknown_0063A880@@YI_NPAVTeamTypeClass@@H@Z=0063a880

bool TActionClass::unknown_func_6b2810(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_30 != 0 && unknown_44 != -1) {
        return Unknown_0063A880((TeamTypeClass *)unknown_30, unknown_44);
    }
    return false;
}


