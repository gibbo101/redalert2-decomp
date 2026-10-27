// int TechnoClass::unknown_6d85e0(int index) (0x006D85E0)
// Whether index names a weapon: -1, 0 or 1, or a turret weapon below the
// type's WeaponCount.
#include "shared/techno.hpp"
// @ref ?Has_Turret_Weapons@TechnoTypeClass@@QBE_NXZ=006df680

int TechnoClass::unknown_6d85e0(int index)
{
    bool basic = index < 2;
    bool turret = unknown_slot32()->Has_Turret_Weapons() && index < unknown_slot32()->WeaponCount;
    if (index >= -1 && (basic || turret)) {
        return 1;
    }
    return 0;
}
