// void AircraftClass::unknown_slot119(int mission, int unknown2, int unknown3) (0x0041B1A0, slot 119)
// FootClass's override of the mission, except that missions 4, 26 and 27
// are only replaced by one another.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot119@FootClass@@UAEXHHH@Z=004c7ac0

void AircraftClass::unknown_slot119(int mission, int unknown2, int unknown3)
{
    if ((Mission == 4 || (Mission > 25 && Mission <= 27)) && mission != 4 && (mission <= 25 || mission > 27)) {
        return;
    }
    FootClass::unknown_slot119(mission, unknown2, unknown3);
}
