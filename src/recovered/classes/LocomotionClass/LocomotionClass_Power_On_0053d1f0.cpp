// bool __stdcall LocomotionClass::Power_On() (0x0053D1F0, ILocomotion 22)
#include "shared/locomotion.hpp"

bool __stdcall LocomotionClass::Power_On()
{
    Powered = true;
    return Is_Powered();
}
