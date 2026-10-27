// bool __stdcall FlyLocomotionClass::Is_Moving_Now() (0x004BC230, ILocomotion 32)
// Any speed.
#include "shared/fly_locomotion.hpp"
// @ref __real@8@00000000000000000000=0079b610

bool __stdcall FlyLocomotionClass::Is_Moving_Now()
{
    if (unknown_48 == 0.0) {
        return false;
    }
    return true;
}
