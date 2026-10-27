// int __stdcall FlyLocomotionClass::Get_Status() (0x004BF5D0, ILocomotion 36)
// 1 or 0 for the flags at +0x51 and +0x50; otherwise 2 moving, 3 not.
#include "shared/fly_locomotion.hpp"

int __stdcall FlyLocomotionClass::Get_Status()
{
    if (unknown_51) {
        return 1;
    }
    if (unknown_50) {
        return 0;
    }
    return Is_Moving() ? 2 : 3;
}
