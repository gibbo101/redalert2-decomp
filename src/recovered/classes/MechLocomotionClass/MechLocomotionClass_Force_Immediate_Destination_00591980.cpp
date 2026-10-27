// void __stdcall MechLocomotionClass::Force_Immediate_Destination(CoordStruct coord) (0x00591980, ILocomotion 30)
#include "shared/mech_locomotion.hpp"

void __stdcall MechLocomotionClass::Force_Immediate_Destination(CoordStruct coord)
{
    unknown_24 = CoordStruct(coord.X, coord.Y, coord.Z);
}
