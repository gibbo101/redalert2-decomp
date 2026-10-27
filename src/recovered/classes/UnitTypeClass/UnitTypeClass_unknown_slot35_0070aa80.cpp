// ObjectClass *UnitTypeClass::unknown_slot35(HouseClass *house) const (0x0070AA80)
// A new vehicle of this type for the house (RA1: Create_One_Of).
#include "shared/unit_type.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0UnitClass@@QAE@PAVUnitTypeClass@@PAVHouseClass@@@Z=006fa400

ObjectClass *UnitTypeClass::unknown_slot35(HouseClass *house) const
{
    return (ObjectClass *)new UnitClass((UnitTypeClass *)this, house);
}
