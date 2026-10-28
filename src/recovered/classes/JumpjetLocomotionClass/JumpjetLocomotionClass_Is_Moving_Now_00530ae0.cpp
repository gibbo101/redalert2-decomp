// bool __stdcall JumpjetLocomotionClass::Is_Moving_Now() (0x00530AE0, ILocomotion 32)
// Moving in every state but 0 and 2 (+0x4C).
#include "shared/jumpjet_locomotion.hpp"

bool __stdcall JumpjetLocomotionClass::Is_Moving_Now()
{
    if (unknown_4c != 0 && unknown_4c != 2) {
        return true;
    }
    return false;
}
