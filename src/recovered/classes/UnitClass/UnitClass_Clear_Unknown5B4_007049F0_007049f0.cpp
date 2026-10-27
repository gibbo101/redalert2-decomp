// Clears the recorded +0x5B4 value and notifies virtual slot71 when set.
#include "shared/unit.hpp"
bool UnitClass::Clear_Unknown5B4_007049F0()
{
    if (unknown_5b4 != -1) {
        unknown_5b4 = -1;
        unknown_slot71(2);
        return true;
    }
    return false;
}
