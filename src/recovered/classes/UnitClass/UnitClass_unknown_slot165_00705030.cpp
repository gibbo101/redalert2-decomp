// double UnitClass::unknown_slot165() (0x00705030, slot 165)
// For harvesters and weeders the fill ratio (the stored total over the
// type's Storage); 0 for everything else.
#include "shared/unit.hpp"
// @ref ?unknown_69ae10@UnknownQuad@@QBEMXZ=0069ae10

double UnitClass::unknown_slot165()
{
    if (!Type->Harvester && !Type->Weeder) {
        return 0.0;
    }
    return unknown_294.unknown_69ae10() / Type->Storage;
}
