// CoordStruct __stdcall HoverLocomotionClass::Head_To_Coord() (0x004FC960, ILocomotion 6)
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080

CoordStruct __stdcall HoverLocomotionClass::Head_To_Coord()
{
    if (unknown_24 != unknown_coord_a41080) {
        return CoordStruct(unknown_24.X, unknown_24.Y, unknown_24.Z);
    }
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
