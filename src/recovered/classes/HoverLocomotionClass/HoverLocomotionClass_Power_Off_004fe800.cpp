// bool __stdcall HoverLocomotionClass::Power_Off() (0x004FE800, ILocomotion 23)
// A powered unit on a mission starts drifting; a moving one stops.
#include "shared/hover_locomotion.hpp"
// @ref ?Power_Off@LocomotionClass@@UAG_NXZ=0053d210

bool __stdcall HoverLocomotionClass::Power_Off()
{
    if (Is_Powered() && LinkedTo->Mission != 0 && LinkedTo->Mission != 7) {
        Start_Drift();
    }
    if (Is_Moving()) {
        Stop_Moving();
    }
    return LocomotionClass::Power_Off();
}
