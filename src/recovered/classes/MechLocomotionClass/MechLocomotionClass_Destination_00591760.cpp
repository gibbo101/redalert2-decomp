// CoordStruct __stdcall MechLocomotionClass::Destination() (0x00591760, ILocomotion 5)
// The destination while moving, otherwise none.
#include "shared/mech_locomotion.hpp"
// @ref ?unknown_coord_a70b18@@3UCoordStruct@@A=00a70b18

CoordStruct __stdcall MechLocomotionClass::Destination()
{
    if (Is_Moving()) {
        return CoordStruct(unknown_18.X, unknown_18.Y, unknown_18.Z);
    }
    return CoordStruct(unknown_coord_a70b18.X, unknown_coord_a70b18.Y, unknown_coord_a70b18.Z);
}
