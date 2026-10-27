// int TechnoClass::unknown_slot188(int arg1) (0x006D31E0, slot 188)
// A guard range: -1 for -1; for 0 the type's GuardRange unless slot 193
// holds (else 0); otherwise twice the GuardRange or, without one, twice the
// longer of the two slot 85 ranges, clamped to 0x700..0x1000 for 2 and to
// 0..0x1000 for the rest.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"

int TechnoClass::unknown_slot188(int arg1)
{
    if (arg1 == -1) {
        return -1;
    }
    if (arg1 == 0) {
        bool flag = unknown_slot193();
        if (unknown_slot32()->GuardRange.Value != 0 && !flag) {
            return unknown_slot32()->GuardRange.Value;
        }
        return 0;
    }
    int range = unknown_slot32()->GuardRange.Value;
    if (range == 0) {
        range = (unknown_slot85(0) > unknown_slot85(1)) ? unknown_slot85(0) : unknown_slot85(1);
    }
    range *= 2;
    if (arg1 == 2) {
        if (range < 0x700) {
            return 0x700;
        }
        if (range > 0x1000) {
            return 0x1000;
        }
    } else {
        if (range < 0) {
            return 0;
        }
        if (range > 0x1000) {
            range = 0x1000;
        }
    }
    return range;
}
