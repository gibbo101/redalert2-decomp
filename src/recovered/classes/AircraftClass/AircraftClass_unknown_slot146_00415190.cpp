// int AircraftClass::unknown_slot146() (0x00415190, slot 146)
// Without a target: clear it and queue mission 4. With one but no +0x494:
// slot 260 on it. Within the rules distance (+0x468): queue mission 27 and
// use up one of +0x5BB. Always 3.
#include "shared/aircraft.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Distance_To@ObjectClass@@QBEHPBVAbstractClass@@@Z=005d4ce0

int AircraftClass::unknown_slot146()
{
    if (unknown_228 == 0) {
        unknown_slot260(0, 1);
        unknown_slot116(4, false);
        return 3;
    }
    if (unknown_494 == 0) {
        unknown_slot260(unknown_228, 1);
        return 3;
    }
    if (Distance_To(unknown_228) <= Rules->unknown_468) {
        unknown_slot116(27, false);
        unknown_5bb--;
    }
    return 3;
}
