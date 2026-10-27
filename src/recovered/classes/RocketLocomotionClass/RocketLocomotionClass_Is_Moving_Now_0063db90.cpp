// bool __stdcall RocketLocomotionClass::Is_Moving_Now() (0x0063DB90, ILocomotion 32)
// States 3 to 5.
#include "shared/rocket_locomotion.hpp"

bool __stdcall RocketLocomotionClass::Is_Moving_Now()
{
    if (unknown_40 >= 3 && unknown_40 <= 5) {
        return true;
    }
    return false;
}
