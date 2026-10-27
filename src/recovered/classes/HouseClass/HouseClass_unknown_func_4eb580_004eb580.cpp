// FactoryClass *HouseClass::unknown_func_4eb580(int kind, bool naval, int arg3) (0x004EB580)
// The house's factory for an object kind (+0x52D8..+0x52F8).
// Cases are object kinds: 1 unit, 2/3 aircraft, 6/7 building, 15/16
// infantry, 40 (all hypotheses); arg3 5 picks the second building entry.
#include "shared/techno.hpp"

FactoryClass *HouseClass::unknown_func_4eb580(int kind, bool naval, int arg3)
{
    switch (kind) {
    case 15:
    case 16:
        return unknown_52dc;
    case 1:
    case 40:
        if (naval) {
            return unknown_52e4;
        }
        return unknown_52e0;
    case 6:
    case 7:
        if (arg3 == 5) {
            return unknown_52f8;
        }
        return unknown_52e8;
    case 2:
    case 3:
        return unknown_52d8;
    }
    return 0;
}
