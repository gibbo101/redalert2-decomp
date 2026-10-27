// bool TechnoClass::unknown_6d1440() (0x006D1440)
// Whether the object at +0x408 exists and its 0x00613B60 is positive.
#include "shared/techno.hpp"
// @ref ?unknown_613b60@UnknownTechno408@@QAEHXZ=00613b60

bool TechnoClass::unknown_6d1440()
{
    if (unknown_408 == 0) {
        return false;
    }
    return unknown_408->unknown_613b60() > 0 ? true : false;
}
