// CoordStruct __stdcall FlyLocomotionClass::Destination() (0x004BC250, ILocomotion 5)
#include "shared/fly_locomotion.hpp"
// @ref ?unknown_coord_865df8@@3UCoordStruct@@A=00865df8

CoordStruct __stdcall FlyLocomotionClass::Destination()
{
    if (Is_Moving()) {
        return CoordStruct(unknown_1c.X, unknown_1c.Y, unknown_1c.Z);
    }
    return CoordStruct(unknown_coord_865df8.X, unknown_coord_865df8.Y, unknown_coord_865df8.Z);
}
