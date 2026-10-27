// bool __stdcall ShipLocomotionClass::Is_Ok_To_End() (0x00675A30, IPiggyback 5)
// Once stopped while unlocked and carrying a locomotor.
#include "shared/ship_locomotion.hpp"

bool __stdcall ShipLocomotionClass::Is_Ok_To_End()
{
    if (!Is_Moving() && Piggybacker != 0 && unknown_65) {
        return true;
    }
    return false;
}
