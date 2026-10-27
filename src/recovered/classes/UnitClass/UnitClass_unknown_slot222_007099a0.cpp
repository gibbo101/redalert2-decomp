// bool UnitClass::unknown_slot222(HouseClass *house, int arg2) (0x007099A0, slot 222)
// house is the new owner (hypothesis: a change of owner). Nothing for the current
// owner; otherwise clears +0x5B8, passes the change on to the unit at
// +0x5B0 (which keeps it, flagged at its +0x5B8), then the foot behaviour
// with arg2 forced to 1.
#include "shared/unit.hpp"
// @ref ?unknown_slot222@FootClass@@UAE_NPAVHouseClass@@H@Z=004ca7d0

bool UnitClass::unknown_slot222(HouseClass *house, int arg2)
{
    if (house != House) {
        unknown_5b8 = false;
        UnitClass *unit = (UnitClass *)unknown_5b0;
        if (unit) {
            unit->unknown_slot222(house, 1);
            unknown_5b0 = unit;
            unit->unknown_5b8 = true;
        }
        return FootClass::unknown_slot222(house, 1);
    }
    return false;
}
