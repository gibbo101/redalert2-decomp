// void __stdcall HoverLocomotionClass::Stop_Moving() (0x004FDF40, ILocomotion 18)
// Drops a destination that differs from the head-to coordinate.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080

void __stdcall HoverLocomotionClass::Stop_Moving()
{
    if (unknown_18 != unknown_24) {
        unknown_18 = unknown_coord_a41080;
        LinkedTo->unknown_4d0 = -1;
    }
}
