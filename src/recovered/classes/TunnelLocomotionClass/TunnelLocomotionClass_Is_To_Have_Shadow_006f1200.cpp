// bool __stdcall TunnelLocomotionClass::Is_To_Have_Shadow() (0x006F1200, ILocomotion 8)
// Only above ground (states 0, 1, 2, 6, 7).
#include "shared/tunnel_locomotion.hpp"

bool __stdcall TunnelLocomotionClass::Is_To_Have_Shadow()
{
    if (unknown_18 == 0 || unknown_18 == 1 || unknown_18 == 7 || unknown_18 == 2 || unknown_18 == 6) {
        return true;
    }
    return false;
}
