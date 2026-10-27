// void AircraftClass::unknown_slot118(int mission) (0x0041B120, slot 118)
// Sets the mission, except that missions 4, 26 and 27 are only replaced by
// one another.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot118@MissionClass@@UAEXH@Z=00594710

void AircraftClass::unknown_slot118(int mission)
{
    if ((Mission == 4 || (Mission > 25 && Mission <= 27)) && mission != 4 && (mission <= 25 || mission > 27)) {
        return;
    }
    MissionClass::unknown_slot118(mission);
}
