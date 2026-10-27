// bool __stdcall DriveLocomotionClass::Is_Piggybacking() (0x004A4C80, IPiggyback 7)
#include "shared/drive_locomotion.hpp"

bool __stdcall DriveLocomotionClass::Is_Piggybacking()
{
    return Piggybacker != 0;
}
