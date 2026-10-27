// int TechnoClass::unknown_slot85(int arg1) (0x006CD810, slot 85)
// The +0xB4 value of weapon arg1, or 0.
#include "shared/techno.hpp"

int TechnoClass::unknown_slot85(int arg1)
{
    WeaponTypeClass *weapon = unknown_slot231(arg1)->WeaponType;
    if (weapon) {
        return weapon->unknown_b4;
    }
    return 0;
}
