// int TechnoClass::unknown_6d84a0() (0x006D84A0)
// unknown_10c when the type test 0x006DF680 holds, else 0.
#include "shared/techno.hpp"
// @ref ?Has_Turret_Weapons@TechnoTypeClass@@QBE_NXZ=006df680

int TechnoClass::unknown_6d84a0()
{
    if (unknown_slot32()->Has_Turret_Weapons()) {
        return unknown_10c;
    }
    return 0;
}
