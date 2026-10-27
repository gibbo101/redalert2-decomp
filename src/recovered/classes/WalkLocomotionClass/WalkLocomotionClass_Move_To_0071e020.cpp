// void __stdcall WalkLocomotionClass::Move_To(CoordStruct to) (0x0071E020, ILocomotion 17)
// Unless the linked object is busy (slots 201, 111, 112), heads for the
// coordinate (raised on flagged cells); a null coordinate without a
// head-to coordinate ends the walk (slot 308).
#include "shared/walk_locomotion.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_coord_af9060@@3UCoordStruct@@A=00af9060
// @ref ?Unknown_006A29B0@@YIHH@Z=006a29b0

void __stdcall WalkLocomotionClass::Move_To(CoordStruct to)
{
    if (!LinkedTo->unknown_slot201() && !LinkedTo->unknown_slot111() && !LinkedTo->unknown_slot112()) {
        unknown_1c = CoordStruct(to.X, to.Y, to.Z);
        if (to != unknown_coord_af9060) {
            to = CoordStruct(to.X, to.Y, to.Z);
            if (Loco_Cell(to)->Flags & 0x100) {
                unknown_1c.Z += Unknown_006A29B0(60);
            }
            unknown_34 = true;
        } else if (unknown_28 == unknown_coord_af9060) {
            bool moving = unknown_34;
            unknown_34 = false;
            if (moving) {
                LinkedTo->unknown_slot308();
            }
        }
    }
}
