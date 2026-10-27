// bool __stdcall DriveLocomotionClass::Is_Ok_To_End() (0x0049FA70, IPiggyback 5)
// Once stopped while unlocked and carrying a locomotor.
#include "shared/drive_locomotion.hpp"

bool __stdcall DriveLocomotionClass::Is_Ok_To_End()
{
    if (!Is_Moving() && Piggybacker != 0 && unknown_65) {
        return true;
    }
    return false;
}
