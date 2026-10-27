// bool TechnoClass::unknown_slot261(bool arg1, bool arg2) (0x006D48F0, slot 261)
// Calls 0x00615360 when slot 279 is false and slot 242 true; returns false.
#include "shared/techno.hpp"
// @ref ?unknown_615360@TechnoClass@@QAEXXZ=00615360

bool TechnoClass::unknown_slot261(bool arg1, bool arg2)
{
    if (!unknown_slot279() && unknown_slot242()) {
        unknown_615360();
    }
    return false;
}
