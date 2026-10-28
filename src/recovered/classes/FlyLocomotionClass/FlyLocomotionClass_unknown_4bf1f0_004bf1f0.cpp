// void FlyLocomotionClass::unknown_4bf1f0() (0x004BF1F0)
// Unless the linked techno is on mission 7 or passes its check 0x006D1470,
// nothing happens. An airport-bound aircraft that is out of radio contact
// with the building in its cell calls its slot 261 (false, true); otherwise
// the flight state resets (+0x50/+0x52 cleared, +0x51 set, +0x38 zero).
#include "shared/fly_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
// @ref ?unknown_6d1470@TechnoClass@@QAE_NXZ=006d1470
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?Is_Radio_Contact@RadioClass@@QBE_NPAVTechnoClass@@@Z=00636e30

void FlyLocomotionClass::unknown_4bf1f0()
{
    if (LinkedTo->unknown_slot91() == 7 || !LinkedTo->unknown_6d1470()) {
        if (LinkedTo->Kind_Of() == 2) {
            AircraftClass *aircraft = (AircraftClass *)LinkedTo;
            if (aircraft->Type->AirportBound) {
                CellClass *cell = (CellClass *)aircraft->unknown_slot105();
                if (!LinkedTo->Is_Radio_Contact((TechnoClass *)cell->unknown_4717b0())) {
                    aircraft->unknown_slot261(false, true);
                    return;
                }
            }
        }
        unknown_50 = false;
        unknown_51 = true;
        unknown_52 = false;
        unknown_38 = 0;
    }
}
