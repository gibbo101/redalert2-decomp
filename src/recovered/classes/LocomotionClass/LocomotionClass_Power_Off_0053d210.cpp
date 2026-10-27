// bool __stdcall LocomotionClass::Power_Off() (0x0053D210, ILocomotion 23)
#include "shared/locomotion.hpp"

bool __stdcall LocomotionClass::Power_Off()
{
    Powered = false;
    return Is_Powered();
}
