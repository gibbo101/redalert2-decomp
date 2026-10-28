// bool __stdcall FlyLocomotionClass::Is_Moving() (0x004BC200, ILocomotion 4)
// Flying somewhere, or still above the ground (+0x240).
#include "shared/fly_locomotion.hpp"
// @ref __real@4@00000000000000000000=0079a738

bool __stdcall FlyLocomotionClass::Is_Moving()
{
    return unknown_34 || LinkedTo->unknown_240 > 0.0f;
}
