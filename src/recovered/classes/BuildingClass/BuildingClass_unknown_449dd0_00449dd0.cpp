// int BuildingClass::unknown_449dd0() (0x00449DD0)
// 0 when slot 111 holds or unknown_530 is clear. Otherwise the type's
// +0xC6C, plus its +0xC74 when unknown_539 is set, plus the +0xC6C of each
// of the three upgrades in unknown_4c0 when unknown_5c6 is not zero.
#include "shared/building.hpp"

int BuildingClass::unknown_449dd0()
{
    if (unknown_slot111() || !unknown_530) {
        return 0;
    }
    int total = Type->PowerDrain_c6c;
    if (unknown_539) {
        total += Type->ExtraPowerDrain_c74;
    }
    if (unknown_5c6) {
        for (int index = 0; index < 3; index++) {
            if (unknown_4c0[index]) {
                total += ((BuildingTypeClass *)unknown_4c0[index])->PowerDrain_c6c;
            }
        }
    }
    return total;
}
