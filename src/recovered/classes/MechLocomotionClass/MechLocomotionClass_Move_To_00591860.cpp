// void __stdcall MechLocomotionClass::Move_To(CoordStruct to) (0x00591860, ILocomotion 17)
// Unless the linked object is busy (slots 201, 202, 111, 112), heads for
// the coordinate (raised on flagged cells) and starts moving.
#include "shared/mech_locomotion.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006A29B0@@YIHH@Z=006a29b0

void __stdcall MechLocomotionClass::Move_To(CoordStruct to)
{
    if (!LinkedTo->unknown_slot201() && !LinkedTo->unknown_slot202()
        && !LinkedTo->unknown_slot111() && !LinkedTo->unknown_slot112()) {
        // The original copies the argument member by member first.
        to = CoordStruct(to.X, to.Y, to.Z);
        unknown_18 = to;
        if (Loco_Cell(to)->Flags & 0x100) {
            unknown_18.Z += Unknown_006A29B0(60);
        }
        unknown_30 = true;
    }
}
