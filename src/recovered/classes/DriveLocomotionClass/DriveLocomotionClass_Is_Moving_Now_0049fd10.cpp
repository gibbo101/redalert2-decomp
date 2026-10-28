// bool __stdcall DriveLocomotionClass::Is_Moving_Now() (0x0049FD10, ILocomotion 32)
// Turning, or moving toward a head-to coordinate with speed (slot 303).
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ?Is_Rotating@FacingClass@@QBE_NXZ=004b8c90

bool __stdcall DriveLocomotionClass::Is_Moving_Now()
{
    if (LinkedTo->unknown_2e0.Is_Rotating()) {
        return true;
    }
    if (Is_Moving() && unknown_40 != unknown_coord_852998 && LinkedTo->unknown_slot303() > 0) {
        return true;
    }
    return false;
}
