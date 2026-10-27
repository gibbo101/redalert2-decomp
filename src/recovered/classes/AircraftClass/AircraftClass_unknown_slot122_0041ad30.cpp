// bool AircraftClass::unknown_slot122() (0x0041AD30, slot 122)
// False on missions 6 and 21 or while locked (+0x5BA); otherwise +0x5BC.
#include "shared/aircraft.hpp"

bool AircraftClass::unknown_slot122()
{
    if (Mission == 6 || Mission == 21 || unknown_5ba) {
        return false;
    }
    return unknown_5bc ? true : false;
}
