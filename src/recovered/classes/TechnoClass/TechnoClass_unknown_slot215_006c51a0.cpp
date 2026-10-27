// bool TechnoClass::unknown_slot215(AbstractClass *target) (0x006C51A0, slot 215)
// Slot 212 with slot 227's weapon when that weapon's type has +0x112,
// otherwise slot 213.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot215(AbstractClass *target)
{
    int weapon = unknown_slot227();
    WeaponStruct *slot = unknown_slot231(weapon);
    if (slot != 0 && slot->WeaponType != 0 && slot->WeaponType->unknown_112) {
        return unknown_slot212(target, weapon);
    } else {
        return unknown_slot213(target);
    }
}
