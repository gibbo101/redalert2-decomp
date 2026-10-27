// bool TechnoClass::unknown_slot225() (0x006D84D0, slot 225)
// The +0x126 flag of the slot 229 weapon.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot225()
{
    WeaponStruct *weapon = unknown_slot229();
    if (weapon && weapon->WeaponType) {
        return weapon->WeaponType->unknown_126;
    }
    return false;
}
