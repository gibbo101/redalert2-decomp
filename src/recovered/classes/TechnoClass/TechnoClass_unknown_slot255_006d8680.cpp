// void TechnoClass::unknown_slot255(int arg1) (0x006D8680, slot 255)
// Sets unknown_170 and its frame when arg1, then slot 266.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TechnoClass::unknown_slot255(TechnoClass *techno)
{
    if (techno) {
        unknown_170 = true;
        unknown_174 = Frame;
    }
    unknown_slot266();
}
