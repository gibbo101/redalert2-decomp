// CoordStruct __stdcall ShipLocomotionClass::Head_To_Coord() (0x00675D70, ILocomotion 6)
// The head-to coordinate when set, otherwise where the linked object is.
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8

CoordStruct __stdcall ShipLocomotionClass::Head_To_Coord()
{
    if (unknown_40 != unknown_coord_ab91c8) {
        return CoordStruct(unknown_40.X, unknown_40.Y, unknown_40.Z);
    }
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
