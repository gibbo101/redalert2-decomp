// FootClass *FootClass::unknown_4ccfc0() (0x004CCFC0)
// The first passenger leaves this transport: a Gunner type left empty runs
// slot 281, and the type's LeaveTransportSound plays at the transport.
#include "shared/foot.hpp"
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?Unknown_00714290@@YIXHABUCoordStruct@@H@Z=00714290

// A sound played at a coordinate (0x00714290; fastcall as 0x00713E60).
void __fastcall Unknown_00714290(int sound, CoordStruct const &coord, int arg3);

FootClass *FootClass::unknown_4ccfc0()
{
    FootClass *passenger = (FootClass *)Cargo.unknown_4689f0();
    if (unknown_slot32()->Gunner && Cargo.Count == 0) {
        unknown_slot281((int)passenger);
    }
    if (passenger != 0 && unknown_slot32()->LeaveTransportSound != -1) {
        Unknown_00714290(unknown_slot32()->LeaveTransportSound, CoordStruct(Coord), 0);
    }
    return passenger;
}
