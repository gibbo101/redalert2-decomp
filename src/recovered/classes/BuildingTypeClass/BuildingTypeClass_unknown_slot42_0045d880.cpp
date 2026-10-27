// bool BuildingTypeClass::unknown_slot42(Cell const &cell, HouseClass *house) const (0x0045D880)
// PlaceAnywhere types may always be placed.
#include "shared/building_type.hpp"
// @ref ?unknown_slot42@TechnoTypeClass@@UBE_NABVCell@@PAVHouseClass@@@Z=006de0e0

bool BuildingTypeClass::unknown_slot42(Cell const &cell, HouseClass *house) const
{
    if (PlaceAnywhere) {
        return true;
    }
    return TechnoTypeClass::unknown_slot42(cell, house);
}
