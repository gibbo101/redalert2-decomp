// void AircraftClass::unknown_slot116(int mission, bool commence) (0x0041B160, slot 116)
// Queues the mission, except that missions 4, 26 and 27 are only replaced
// by one another.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot116@MissionClass@@UAEXH_N@Z=00594cb0

void AircraftClass::unknown_slot116(int mission, bool commence)
{
    if ((Mission == 4 || (Mission > 25 && Mission <= 27)) && mission != 4 && (mission <= 25 || mission > 27)) {
        return;
    }
    MissionClass::unknown_slot116(mission, commence);
}
