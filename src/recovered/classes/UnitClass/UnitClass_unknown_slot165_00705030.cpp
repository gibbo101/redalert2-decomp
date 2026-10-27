// double UnitClass::unknown_slot165() (0x00705030, slot 165)
// For harvesters and weeders the fill ratio (the stored total over the
// type's Storage); 0 for everything else.
#include "shared/unit.hpp"
// @ref ?Get_Total_Amount@StorageClass@@QBEMXZ=0069ae10

double UnitClass::unknown_slot165()
{
    if (!Type->Harvester && !Type->Weeder) {
        return 0.0;
    }
    return unknown_294.Get_Total_Amount() / Type->Storage;
}
