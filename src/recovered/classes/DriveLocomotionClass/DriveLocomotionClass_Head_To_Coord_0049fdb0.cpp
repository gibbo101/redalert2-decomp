// CoordStruct __stdcall DriveLocomotionClass::Head_To_Coord() (0x0049FDB0, ILocomotion 6)
// The head-to coordinate when set, otherwise where the linked object is.
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998

CoordStruct __stdcall DriveLocomotionClass::Head_To_Coord()
{
    if (unknown_40 != unknown_coord_852998) {
        return CoordStruct(unknown_40.X, unknown_40.Y, unknown_40.Z);
    }
    CoordStruct coord = LinkedTo->Coord;
    return coord;
}
