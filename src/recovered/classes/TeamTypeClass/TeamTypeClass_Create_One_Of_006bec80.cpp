// TeamClass *TeamTypeClass::Create_One_Of(HouseClass *house) (0x006BEC80)
// Creates a team of this type for the house (the type's owner when none is
// given), unless the type already has its maximum number of teams.
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/anim_type.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Team_Count@HouseClass@@QAEHPAVTeamTypeClass@@@Z=004f35f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0TeamClass@@QAE@PAVTeamTypeClass@@PAVHouseClass@@H@Z=006b7430
// @ref ??_C@_0BC@BODD@Create_One_Of?4?4?4?6?$AA@=007f6e64
// @ref ??_C@_0CB@KPCI@Creating?5a?5new?5team?5named?5?8?$CFs?8?4?6@=007f6e40
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

extern int unknown_a40774;                  // 0x00A40774
extern int unknown_game_mode_a3d298;        // 0x00A3D298

TeamClass *TeamTypeClass::Create_One_Of(HouseClass *house)
{
    Debug_Printf("Create_One_Of...\n");
    if (house == 0) {
        house = Owner;
    }
    if (!unknown_a40774 && Max >= 0) {
        if (!unknown_game_mode_a3d298) {
            if (unknown_d4 >= Max) {
                return 0;
            }
        } else if (house->Team_Count(this) >= Max) {
            return 0;
        }
    }
    Debug_Printf("Creating a new team named '%s'.\n", (char const *)Name);
    return new TeamClass(this, house, 0);
}
