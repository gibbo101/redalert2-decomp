// CoordStruct __stdcall WalkLocomotionClass::Destination() (0x0071DF10, ILocomotion 5)
#include "shared/walk_locomotion.hpp"
// @ref ?unknown_coord_af9060@@3UCoordStruct@@A=00af9060

CoordStruct __stdcall WalkLocomotionClass::Destination()
{
    if (Is_Moving()) {
        return CoordStruct(unknown_1c.X, unknown_1c.Y, unknown_1c.Z);
    }
    return CoordStruct(unknown_coord_af9060.X, unknown_coord_af9060.Y, unknown_coord_af9060.Z);
}
