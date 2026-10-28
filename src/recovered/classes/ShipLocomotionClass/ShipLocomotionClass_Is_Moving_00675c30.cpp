// bool __stdcall ShipLocomotionClass::Is_Moving() (0x00675C30, ILocomotion 4)
// A destination is set, or a head-to coordinate other than where the
// object stands (X and Y).
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8

bool __stdcall ShipLocomotionClass::Is_Moving()
{
    if (unknown_34 != unknown_coord_ab91c8) {
        return true;
    }
    if (unknown_40 != unknown_coord_ab91c8) {
        if (unknown_40.X != Object_Coord(LinkedTo).X || unknown_40.Y != Object_Coord(LinkedTo).Y) {
            return true;
        }
    }
    return false;
}
