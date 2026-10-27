// bool HouseClass::unknown_func_4eb770(int kind, bool naval, int arg3) (0x004EB770)
// The flag per object kind.
// Cases are object kinds: 1 unit, 2/3 aircraft, 6/7 building, 15/16
// infantry, 40 (all hypotheses); arg3 5 picks the second building entry.
#include "shared/techno.hpp"

bool HouseClass::unknown_func_4eb770(int kind, bool naval, int arg3)
{
    switch (kind) {
    case 15:
    case 16:
        return unknown_52fd;
    case 1:
    case 40:
        if (naval) {
            return unknown_52ff;
        }
        return unknown_52fe;
    case 6:
    case 7:
        if (arg3 == 5) {
            return unknown_5304;
        }
        return unknown_5300;
    case 2:
    case 3:
        return unknown_52fc;
    }
    return false;
}
