// bool BuildingClass::unknown_44d7d0() (0x0044D7D0)
// True for a type that is not a gate. A gate outside mission 24, or whose
// +0x2A8 state is not settled (0x00496AB0 or 0x00496B50), is given mission
// 24 again (slots 118, 116, 117) and the answer is false; otherwise the
// answer of unknown_44d880.
#include "shared/building.hpp"
// @ref ?unknown_496ab0@UnknownTimed@@QBE_NXZ=00496ab0
// @ref ?unknown_496b50@UnknownTimed@@QBE_NXZ=00496b50
// @ref ?unknown_496b30@UnknownTimed@@QBE_NXZ=00496b30

bool BuildingClass::unknown_44d7d0()
{
    if (!Type->Gate) {
        return true;
    }
    if (unknown_slot91() != 24 || unknown_2a8.unknown_496ab0() || unknown_2a8.unknown_496b50()) {
        unknown_slot118(-1);
        unknown_slot116(24, false);
        unknown_slot117();
        return false;
    }
    return unknown_44d880();
}
