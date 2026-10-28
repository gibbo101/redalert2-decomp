// bool __stdcall DriveLocomotionClass::Is_Moving() (0x0049FC70, ILocomotion 4)
// A destination is set, or a head-to coordinate other than where the
// object stands (X and Y).
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998

bool __stdcall DriveLocomotionClass::Is_Moving()
{
    if (unknown_34 != unknown_coord_852998) {
        return true;
    }
    if (unknown_40 != unknown_coord_852998) {
        if (unknown_40.X != Object_Coord(LinkedTo).X || unknown_40.Y != Object_Coord(LinkedTo).Y) {
            return true;
        }
    }
    return false;
}
