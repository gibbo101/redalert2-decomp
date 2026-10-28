// Cell HouseClass::unknown_func_4f6a80(int mode) (0x004F6A80)
// The cell under what the leader of the house's first team would attack for a
// target mode (0x006220E0 gives the threat flags): slot 219 of the leader with its
// own center coordinate; the invalid cell without a team or a target.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno.hpp"
#include "shared/object.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?unknown_cell_a40f10@@3VCell@@A=00a40f10
// @ref ?unknown_threat_flags_6220e0@@YIHH@Z=006220e0
// @ref ?unknown_func_6baa60@TeamClass@@QAEPAVFootClass@@XZ=006baa60

int __fastcall unknown_threat_flags_6220e0(int mode);   // 0x006220E0

Cell HouseClass::unknown_func_4f6a80(int mode)
{
    int flags = unknown_threat_flags_6220e0(mode);
    TeamClass *team = 0;
    for (int index = 0; index < Teams.Count(); index++) {
        team = Teams[index];
        if (team->Owner == this) {
            break;
        }
    }
    if (team != 0 && team->Owner == this) {
        FootClass *leader = team->unknown_func_6baa60();
        AbstractClass *target = leader->unknown_slot219(flags, &leader->Center_Coord(), true);
        if (target != 0) {
            return Coord_Cell(target->Center_Coord());
        }
        return unknown_cell_a40f10;
    }
    return unknown_cell_a40f10;
}
