// void __stdcall DriveLocomotionClass::Move_To(COMCoordStruct to) (0x0049FE30, ILocomotion 17)
// Unless the linked object is busy (slots 201, 202, 111, 112), heads for
// the coordinate (raised by the bridge height on flagged cells).
#include "shared/drive_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998

void __stdcall DriveLocomotionClass::Move_To(COMCoordStruct to)
{
    if (!LinkedTo->unknown_slot201() && !LinkedTo->unknown_slot202() && !LinkedTo->unknown_slot111() && !LinkedTo->unknown_slot112()) {
        unknown_34 = CoordStruct(to.X, to.Y, to.Z);
        if (to != unknown_coord_852998) {
            to = CoordStruct(to.X, to.Y, to.Z);
            if (Loco_Cell(to)->Flags & 0x100) {
                unknown_34.Z += unknown_geometry_j;
            }
        }
    }
}
