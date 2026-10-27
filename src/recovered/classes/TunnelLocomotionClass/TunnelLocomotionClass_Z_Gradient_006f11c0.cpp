// int __stdcall TunnelLocomotionClass::Z_Gradient() (0x006F11C0, ILocomotion 15)
// Gradient 2 while digging or surfacing (states 2, 3, 5, 6, 7).
#include "shared/tunnel_locomotion.hpp"
// @ref ?Z_Gradient@LocomotionClass@@UAGHXZ=0053d4b0

int __stdcall TunnelLocomotionClass::Z_Gradient()
{
    if (unknown_18 == 3 || unknown_18 == 2 || unknown_18 == 7 || unknown_18 == 6 || unknown_18 == 5) {
        return 2;
    }
    return LocomotionClass::Z_Gradient();
}
