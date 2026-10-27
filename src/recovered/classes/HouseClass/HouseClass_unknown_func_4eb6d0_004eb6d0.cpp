// void HouseClass::unknown_func_4eb6d0(int kind, bool naval, int arg3) (0x004EB6D0)
// Clears the flag per object kind.
// Cases are object kinds: 1 unit, 2/3 aircraft, 6/7 building, 15/16
// infantry, 40 (all hypotheses); arg3 5 picks the second building entry.
#include "shared/techno.hpp"

void HouseClass::unknown_func_4eb6d0(int kind, bool naval, int arg3)
{
    switch (kind) {
    case 15:
    case 16:
        unknown_52fd = false;
        // fall through
    case 1:
    case 40:
        if (naval) {
            unknown_52ff = false;
        } else {
            unknown_52fe = false;
        }
        break;
    case 6:
    case 7:
        if (arg3 == 5) {
            unknown_5304 = false;
        } else {
            unknown_5300 = false;
        }
        break;
    case 2:
    case 3:
        unknown_52fc = false;
        break;
    }
}
