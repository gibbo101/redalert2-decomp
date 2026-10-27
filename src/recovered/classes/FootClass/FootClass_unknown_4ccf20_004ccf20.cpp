// void FootClass::unknown_4ccf20(FootClass *passenger) (0x004CCF20)
// A given passenger leaves this transport (never called; the other units
// expand it): it leaves the cargo, the type's LeaveTransportSound plays at
// the transport, and a Gunner type left empty runs slot 281.
#include "shared/foot.hpp"
// @ref ?Unknown_00468A70@UnknownCargo@@QAEXPAVFootClass@@@Z=00468a70
// @ref ?Unknown_00714290@@YIXHABUCoordStruct@@H@Z=00714290

// A sound played at a coordinate (0x00714290; fastcall as 0x00713E60).
void __fastcall Unknown_00714290(int sound, CoordStruct const &coord, int arg3);

void FootClass::unknown_4ccf20(FootClass *passenger)
{
    Cargo.Unknown_00468A70(passenger);
    if (passenger != 0 && unknown_slot32()->LeaveTransportSound != -1) {
        Unknown_00714290(unknown_slot32()->LeaveTransportSound, CoordStruct(Coord), 0);
    }
    if (unknown_slot32()->Gunner && Cargo.Count == 0) {
        unknown_slot281((int)passenger);
    }
}
