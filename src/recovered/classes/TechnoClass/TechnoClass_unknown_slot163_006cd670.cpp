// bool TechnoClass::unknown_slot163() (0x006CD670, slot 163)
// Whether slot 230 has a weapon.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot163()
{
    WeaponStruct *weapon = unknown_slot230();
    return weapon != 0 && weapon->WeaponType != 0;
}
