// bool __stdcall ShipLocomotionClass::Is_Moving_Now() (0x00675CD0, ILocomotion 32)
// Turning, or moving toward a head-to coordinate with speed (slot 303).
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?Is_Rotating@FacingClass@@QBE_NXZ=004b8c90

bool __stdcall ShipLocomotionClass::Is_Moving_Now()
{
    if (LinkedTo->unknown_2e0.Is_Rotating()) {
        return true;
    }
    if (Is_Moving() && unknown_40 != unknown_coord_ab91c8 && LinkedTo->unknown_slot303() > 0) {
        return true;
    }
    return false;
}
