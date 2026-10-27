// bool TechnoClass::unknown_slot158() (0x006C7480, slot 158)
// Whether the type's +0xB0 entry is set and starts with a zero byte.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot158()
{
    if (unknown_slot32()->unknown_b0.unknown_00 == 0) {
        return false;
    }
    return *(char const *)unknown_slot32()->unknown_b0.unknown_00 == 0 ? true : false;
}
