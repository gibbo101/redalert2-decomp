// int UnitClass::unknown_slot133() (0x00704680, slot 133)
// Clears +0x5BA; with +0x5C8 set queues mission 5 and answers 1; otherwise
// starts the +0x2A8 change over the type's DeployTime when it is idle and
// continues with the foot behaviour.
#include "shared/unit.hpp"
// @ref ?unknown_496b50@UnknownTimed@@QBE_NXZ=00496b50
// @ref ?unknown_496bc0@UnknownTimed@@QAEXN@Z=00496bc0
// @ref ?unknown_slot133@FootClass@@UAEHXZ=004c38d0

int UnitClass::unknown_slot133()
{
    unknown_5ba = false;
    if (unknown_5c8) {
        unknown_slot116(5, false);
        return 1;
    }
    if (!unknown_2a8.unknown_496b50()) {
        unknown_2a8.unknown_496bc0(Type->DeployTime);
    }
    return FootClass::unknown_slot133();
}
