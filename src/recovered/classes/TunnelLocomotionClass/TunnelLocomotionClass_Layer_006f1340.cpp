// int __stdcall TunnelLocomotionClass::Layer() (0x006F1340, ILocomotion 29)
// Underground (state 4) is layer 0, otherwise 2.
#include "shared/tunnel_locomotion.hpp"

int __stdcall TunnelLocomotionClass::Layer()
{
    return unknown_18 != 4 ? 2 : 0;
}
