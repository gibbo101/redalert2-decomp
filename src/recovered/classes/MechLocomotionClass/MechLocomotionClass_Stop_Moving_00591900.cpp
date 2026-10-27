// void __stdcall MechLocomotionClass::Stop_Moving() (0x00591900, ILocomotion 18)
// Drops the destination; stops unless a head-to coordinate remains.
#include "shared/mech_locomotion.hpp"
// @ref ?unknown_coord_a70b18@@3UCoordStruct@@A=00a70b18

void __stdcall MechLocomotionClass::Stop_Moving()
{
    unknown_18 = unknown_coord_a70b18;
    if (unknown_24 == unknown_coord_a70b18) {
        unknown_30 = false;
    }
}
