// bool __stdcall MechLocomotionClass::Is_Moving_Here(CoordStruct to) (0x00593260, ILocomotion 40)
// The head-to coordinate is in the cell of the coordinate and within the
// height tolerance of it.
#include "shared/mech_locomotion.hpp"
#include "shared/unknown_geometry.hpp"

bool __stdcall MechLocomotionClass::Is_Moving_Here(CoordStruct to)
{
    CoordStruct head = Head_To_Coord();
    if (Coord_Cell(head) == Coord_Cell(to) && abs(head.Z - to.Z) <= unknown_geometry_g) {
        return true;
    }
    return false;
}
