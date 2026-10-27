// void HouseClass::unknown_func_4eb810(int kind, bool naval, int arg3, bool value) (0x004EB810)
// Sets the flag per object kind to a value.
// Cases are object kinds: 1 unit, 2/3 aircraft, 6/7 building, 15/16
// infantry, 40 (all hypotheses); arg3 5 picks the second building entry.
#include "shared/techno.hpp"

void HouseClass::unknown_func_4eb810(int kind, bool naval, int arg3, bool value)
{
    switch (kind) {
    case 15:
    case 16:
        unknown_52fd = value;
        // fall through
    case 1:
    case 40:
        if (naval) {
            unknown_52ff = value;
        } else {
            unknown_52fe = value;
        }
        break;
    case 6:
    case 7:
        if (arg3 == 5) {
            unknown_5304 = value;
        } else {
            unknown_5300 = value;
        }
        break;
    case 2:
    case 3:
        unknown_52fc = value;
        break;
    }
}
