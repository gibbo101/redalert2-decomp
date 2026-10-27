// int AircraftClass::unknown_slot130() (0x0041A080, slot 130)
// At the type's flight level: slot 261 (0, 1) unless in a team, 1.
// Otherwise slot 261 when out of ammunition, slot 163 holds and there is
// no radio contact; with a target, queue mission 1; else FootClass's.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot130@FootClass@@UAEHXZ=004c5900
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10

int AircraftClass::unknown_slot130()
{
    if (unknown_slot108() == Type->Flight_Level()) {
        if (Team == 0) {
            unknown_slot261(0, 1);
        }
        return 1;
    }
    if (unknown_254 == 0 && unknown_slot163() && !In_Radio_Contact()) {
        unknown_slot261(0, 1);
    }
    if (unknown_228 != 0) {
        unknown_slot116(1, false);
        return 1;
    }
    return FootClass::unknown_slot130();
}
