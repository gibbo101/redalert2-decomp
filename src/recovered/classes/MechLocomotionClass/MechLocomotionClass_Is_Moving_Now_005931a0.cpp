// bool __stdcall MechLocomotionClass::Is_Moving_Now() (0x005931A0, ILocomotion 32)
// Turning, or moving toward a head-to coordinate with some speed.
#include "shared/mech_locomotion.hpp"
// @ref ?unknown_coord_a70b18@@3UCoordStruct@@A=00a70b18
// @ref ?Is_Rotating@FacingClass@@QBE_NXZ=004b8c90

bool __stdcall MechLocomotionClass::Is_Moving_Now()
{
    if (LinkedTo->unknown_2e0.Is_Rotating()) {
        return true;
    }
    if (Is_Moving() && unknown_24 != unknown_coord_a70b18 && LinkedTo->unknown_slot303() > 0) {
        return true;
    }
    return false;
}
