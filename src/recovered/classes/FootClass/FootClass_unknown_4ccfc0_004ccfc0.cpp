// FootClass *FootClass::unknown_4ccfc0() (0x004CCFC0)
// The first passenger leaves this transport: a Gunner type left empty runs
// slot 281, and the type's LeaveTransportSound plays at the transport.
#include "shared/foot.hpp"
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?Voc_Static_Add@@YIPAUAudioEvent@@HABUCoordStruct@@I@Z=00714290

FootClass *FootClass::unknown_4ccfc0()
{
    FootClass *passenger = (FootClass *)Cargo.unknown_4689f0();
    if (unknown_slot32()->Gunner && Cargo.Count == 0) {
        unknown_slot281((int)passenger);
    }
    if (passenger != 0 && unknown_slot32()->LeaveTransportSound != -1) {
        Voc_Static_Add(unknown_slot32()->LeaveTransportSound, CoordStruct(Coord), 0);
    }
    return passenger;
}
