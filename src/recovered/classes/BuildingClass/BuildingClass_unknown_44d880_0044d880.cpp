// bool BuildingClass::unknown_44d880() (0x0044D880)
// True for a type that is not a gate, or for a gate in mission 24 whose
// +0x2A8 state reports done (0x00496B30).
#include "shared/building.hpp"
// @ref ?unknown_496b30@UnknownTimed@@QBE_NXZ=00496b30

bool BuildingClass::unknown_44d880()
{
    if (!Type->Gate) {
        return true;
    }
    if (unknown_slot91() == 24 && unknown_2a8.unknown_496b30()) {
        return true;
    }
    return false;
}
