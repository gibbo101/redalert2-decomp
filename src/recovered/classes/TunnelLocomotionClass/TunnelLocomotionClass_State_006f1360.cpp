// int __stdcall TunnelLocomotionClass::State() (0x006F1360, ILocomotion 35)
// The base state, or 7 while tunnelling.
#include "shared/tunnel_locomotion.hpp"
// @ref ?State@LocomotionClass@@UAGHXZ=0053d600

int __stdcall TunnelLocomotionClass::State()
{
    int state = LocomotionClass::State();
    if (state == 0 && unknown_18) {
        state = 7;
    }
    return state;
}
