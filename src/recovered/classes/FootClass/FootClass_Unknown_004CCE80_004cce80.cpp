// void FootClass::Unknown_004CCE80(FootClass *passenger) (0x004CCE80)
// A passenger enters this transport: it joins the cargo, the type's
// EnterTransportSound plays at the transport, and a Gunner type with its
// first passenger runs slot 280.
#include "shared/foot.hpp"
// @ref ?Unknown_00468960@UnknownCargo@@QAEXPAVFootClass@@@Z=00468960
// @ref ?Unknown_00714290@@YIXHABUCoordStruct@@H@Z=00714290

// A sound played at a coordinate (0x00714290; fastcall as 0x00713E60).
void __fastcall Unknown_00714290(int sound, CoordStruct const &coord, int arg3);

void FootClass::Unknown_004CCE80(FootClass *passenger)
{
    Cargo.Unknown_00468960(passenger);
    if (passenger != 0 && unknown_slot32()->EnterTransportSound != -1) {
        Unknown_00714290(unknown_slot32()->EnterTransportSound, CoordStruct(Coord), 0);
    }
    if (unknown_slot32()->Gunner && Cargo.Count == 1) {
        unknown_slot280((int)passenger);
    }
}
