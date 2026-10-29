// UnitTypeClass *HouseClass::Unknown_004EF6F0(TypeList<UnitTypeClass *> const &list) (0x004EF6F0)
// The first unit type of the list this house's country may own (its owner bit
// is the index of the parent country's house type), else 0 (AI expands it for
// Rules HarvesterUnit; Create_Units 0x00660320 calls it for BaseUnit).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/unit.hpp"

UnitTypeClass *HouseClass::Unknown_004EF6F0(TypeList<UnitTypeClass *> const &list)
{
    int owner = 1 << HouseTypeClass::Find_Index(Type->ParentCountry);
    for (int index = 0; index < list.Count(); index++) {
        if (list[index]->Owner & owner) {
            return list[index];
        }
    }
    return 0;
}
