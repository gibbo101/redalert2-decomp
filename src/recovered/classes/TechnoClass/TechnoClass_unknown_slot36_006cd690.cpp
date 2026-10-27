// bool TechnoClass::unknown_slot36() (0x006CD690, slot 36)
// Kind 6 with type flag +0xAD8 and less than full strength.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot36()
{
    if (Kind_Of() != 6) {
        return false;
    }
    return unknown_slot32()->Repairable && Strength != Class_Of()->MaxStrength;
}
