// void UnitClass::unknown_704aa0() (0x00704AA0)
// A standing unit (locomotor not moving, +0x599 clear) restarts its timer at
// +0x2A8 with the type's DeployTime (0x00496B70).
#include "shared/unit.hpp"
// @ref __com_issue_error@4=00795940
// @ref ?unknown_496b70@UnknownTimed@@QAEXN@Z=00496b70

void UnitClass::unknown_704aa0()
{
    if (!Locomotor.Checked()->Is_Moving() && !unknown_599) {
        unknown_2a8.unknown_496b70(Type->DeployTime);
    }
}
