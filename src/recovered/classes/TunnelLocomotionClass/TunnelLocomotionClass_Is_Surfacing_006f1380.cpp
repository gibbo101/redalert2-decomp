// bool __stdcall TunnelLocomotionClass::Is_Surfacing() (0x006F1380, ILocomotion 38)
// States 5 and 6.
#include "shared/tunnel_locomotion.hpp"

bool __stdcall TunnelLocomotionClass::Is_Surfacing()
{
    return unknown_18 == 5 || unknown_18 == 6;
}
