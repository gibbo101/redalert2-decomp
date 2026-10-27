// int __stdcall TunnelLocomotionClass::Visual_Character(bool raw) (0x006F0390, ILocomotion 13)
// Underground (state 4): 4, or 5 for the raw view; otherwise normal.
#include "shared/tunnel_locomotion.hpp"

int __stdcall TunnelLocomotionClass::Visual_Character(bool raw)
{
    if (unknown_18 == 4) {
        return (raw != 0) + 4;
    }
    return 0;
}
