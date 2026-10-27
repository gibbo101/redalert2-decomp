// bool __stdcall TunnelLocomotionClass::Is_Moving() (0x006EFC30, ILocomotion 4)
// Any state but idle.
#include "shared/tunnel_locomotion.hpp"

bool __stdcall TunnelLocomotionClass::Is_Moving()
{
    return unknown_18 ? true : false;
}
