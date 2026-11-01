// void __stdcall TeleportLocomotionClass::Move_To(CoordStruct to) (0x006DFDA0, ILocomotion 17)
// Unless the linked object is busy (slots 201, 202, 111, 112: then its
// +0x494 is cleared), an infantry clears the target cell first; the step
// 0x006E06B0 picks the arrival coordinate, which starts the move, or the
// object is told to stop (slot 260).
#include "shared/teleport_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_ac0280@@3UCoordStruct@@A=00ac0280
// @ref ?unknown_6e06b0@TeleportLocomotionClass@@QAE_NABUCoordStruct@@@Z=006e06b0
// @ref ?unknown_476920@CellClass@@QAEXPBX_N11@Z=00476920

void __stdcall TeleportLocomotionClass::Move_To(CoordStruct to)
{
    if (LinkedTo->unknown_slot201() || LinkedTo->unknown_slot202() || LinkedTo->unknown_slot111() || LinkedTo->unknown_slot112()) {
        LinkedTo->unknown_494 = 0;
        return;
    }
    CoordStruct coord = CoordStruct(to.X, to.Y, to.Z);
    if (LinkedTo->unknown_190 && LinkedTo->Kind_Of() == 15) {
        CellClass &cell = Map[coord];
        cell.unknown_476920(&unknown_coord_ac0280, true, true, false);
    }
    unknown_6e06b0(coord);
    if (unknown_28 != unknown_coord_ac0280) {
        unknown_34 = true;
        unknown_1c = unknown_28;
    } else {
        LinkedTo->unknown_slot260(0, 1);
    }
}
