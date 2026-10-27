// bool __stdcall HoverLocomotionClass::Is_Moving() (0x004FC880, ILocomotion 4)
// A destination or a head-to coordinate is set.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080

bool __stdcall HoverLocomotionClass::Is_Moving()
{
    return unknown_18 != unknown_coord_a41080 || unknown_24 != unknown_coord_a41080;
}
