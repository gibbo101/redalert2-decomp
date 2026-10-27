// CoordStruct __stdcall HoverLocomotionClass::Destination() (0x004FC900, ILocomotion 5)
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080

CoordStruct __stdcall HoverLocomotionClass::Destination()
{
    if (unknown_18 != unknown_coord_a41080) {
        return CoordStruct(unknown_18.X, unknown_18.Y, unknown_18.Z);
    }
    return CoordStruct(unknown_coord_a41080.X, unknown_coord_a41080.Y, unknown_coord_a41080.Z);
}
