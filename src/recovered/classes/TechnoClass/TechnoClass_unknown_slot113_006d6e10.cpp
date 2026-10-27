// bool TechnoClass::unknown_slot113() (0x006D6E10, slot 113)
// Whether the +0x208 object has a nonzero +0x28.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot113()
{
    if (unknown_208 && unknown_208->unknown_28) {
        return true;
    }
    return false;
}
