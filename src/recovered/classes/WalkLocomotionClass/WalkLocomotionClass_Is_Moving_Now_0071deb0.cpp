// bool __stdcall WalkLocomotionClass::Is_Moving_Now() (0x0071DEB0, ILocomotion 32)
// Moving, with speed, toward a head-to coordinate.
#include "shared/walk_locomotion.hpp"
// @ref ?unknown_coord_af9060@@3UCoordStruct@@A=00af9060
// @ref __real@8@00000000000000000000=0079b610

bool __stdcall WalkLocomotionClass::Is_Moving_Now()
{
    if (Is_Moving() && LinkedTo->unknown_468 > 0.0 && unknown_28 != unknown_coord_af9060) {
        return true;
    }
    return false;
}
