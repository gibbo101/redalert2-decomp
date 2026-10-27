// bool __stdcall TunnelLocomotionClass::Is_Moving_Now() (0x006EFC40, ILocomotion 32)
// Moving and not in state 1.
#include "shared/tunnel_locomotion.hpp"

bool __stdcall TunnelLocomotionClass::Is_Moving_Now()
{
    if (Is_Moving() && unknown_18 != 1) {
        return true;
    }
    return false;
}
