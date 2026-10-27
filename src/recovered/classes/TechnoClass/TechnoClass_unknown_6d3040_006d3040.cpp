// void TechnoClass::unknown_6d3040(TechnoClass *killer) (0x006D3040)
// Destroys every passenger: each leaves its team, is detached from the
// cargo, gets slot 55 (killer) and is deleted.
#include "shared/techno.hpp"
// @ref ?unknown_468a10@UnknownCargo@@QBEPAVObjectClass@@XZ=00468a10
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?unknown_6b8fb0@UnknownPassengerTeam@@QAEXPAVObjectClass@@H_N@Z=006b8fb0

void TechnoClass::unknown_6d3040(TechnoClass *killer)
{
    while (Cargo.Object != 0) {
        ObjectClass *passenger = Cargo.unknown_468a10();
        if (((UnknownPassengerView *)passenger)->Team != 0) {
            ((UnknownPassengerView *)passenger)->Team->unknown_6b8fb0(passenger, -1, false);
        }
        passenger = Cargo.unknown_4689f0();
        if (passenger != 0) {
            passenger->unknown_slot55(killer);
            delete passenger;
        }
    }
}
