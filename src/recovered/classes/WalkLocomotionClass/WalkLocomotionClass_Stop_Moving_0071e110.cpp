// void __stdcall WalkLocomotionClass::Stop_Moving() (0x0071E110, ILocomotion 18)
// Drops the destination; without a head-to coordinate the walk ends and
// the linked object is told (slot 308).
#include "shared/walk_locomotion.hpp"
// @ref ?unknown_coord_af9060@@3UCoordStruct@@A=00af9060

void __stdcall WalkLocomotionClass::Stop_Moving()
{
    unknown_1c = unknown_coord_af9060;
    if (unknown_28 == unknown_coord_af9060) {
        unknown_34 = false;
        unknown_36 = false;
        LinkedTo->unknown_slot308();
    }
}
