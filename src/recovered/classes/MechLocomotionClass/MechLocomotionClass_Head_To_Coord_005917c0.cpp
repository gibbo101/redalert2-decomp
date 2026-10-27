// CoordStruct __stdcall MechLocomotionClass::Head_To_Coord() (0x005917C0, ILocomotion 6)
// The head-to coordinate when set, otherwise where the linked object is.
#include "shared/mech_locomotion.hpp"
// @ref ?unknown_coord_a70b18@@3UCoordStruct@@A=00a70b18

CoordStruct __stdcall MechLocomotionClass::Head_To_Coord()
{
    if (unknown_24 != unknown_coord_a70b18) {
        return CoordStruct(unknown_24.X, unknown_24.Y, unknown_24.Z);
    }
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
