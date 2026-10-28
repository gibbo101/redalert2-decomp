// bool __stdcall FlyLocomotionClass::Power_Off() (0x004BF4A0, ILocomotion 23)
// A moving aircraft starts drifting (a random 20..30, either way) and stops.
#include "shared/fly_locomotion.hpp"
// @ref ?Power_Off@LocomotionClass@@UAG_NXZ=0053d210

bool __stdcall FlyLocomotionClass::Power_Off()
{
    if (Is_Moving()) {
        Start_Drift();
        Stop_Moving();
        unknown_58 = 0;
    }
    return LocomotionClass::Power_Off();
}
