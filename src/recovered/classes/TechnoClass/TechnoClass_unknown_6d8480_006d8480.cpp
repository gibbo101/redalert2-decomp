// int TechnoClass::unknown_6d8480() (0x006D8480)
// Copies +0x100 into +0x104 and reports whether the value changed.
#include "shared/techno.hpp"

int TechnoClass::unknown_6d8480()
{
    int changed = unknown_100 != unknown_104;
    unknown_104 = unknown_100;
    return changed;
}
