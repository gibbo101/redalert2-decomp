// CoordStruct __stdcall JumpjetLocomotionClass::Destination() (0x0052F360, ILocomotion 5)
// The destination while moving, otherwise the null coordinate.
#include "shared/jumpjet_locomotion.hpp"
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0

CoordStruct __stdcall JumpjetLocomotionClass::Destination()
{
    if (Is_Moving()) {
        return CoordStruct(unknown_3c.X, unknown_3c.Y, unknown_3c.Z);
    }
    return CoordStruct(unknown_coord_a6e3e0.X, unknown_coord_a6e3e0.Y, unknown_coord_a6e3e0.Z);
}
