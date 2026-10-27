// bool UnitClass::unknown_slot159() (0x00707950, slot 159)
// True when the state at +0x2A8 is in none of its three active phases.
#include "shared/unit.hpp"
// @ref ?unknown_496a90@UnknownTimed@@QBE_NXZ=00496a90
// @ref ?unknown_496ab0@UnknownTimed@@QBE_NXZ=00496ab0
// @ref ?unknown_496b30@UnknownTimed@@QBE_NXZ=00496b30

bool UnitClass::unknown_slot159()
{
    if (unknown_2a8.unknown_496a90() || unknown_2a8.unknown_496ab0() || unknown_2a8.unknown_496b30()) {
        return false;
    }
    return true;
}
