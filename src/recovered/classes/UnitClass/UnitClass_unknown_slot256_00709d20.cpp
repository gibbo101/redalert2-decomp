// void UnitClass::unknown_slot256() (0x00709D20, slot 256)
// Clears the flag at +0x170, runs slot 266 and forgets +0x40C/+0x410.
#include "shared/unit.hpp"

void UnitClass::unknown_slot256()
{
    unknown_170 = false;
    unknown_slot266();
    unknown_40c = 0;
    unknown_410 = 0;
}
