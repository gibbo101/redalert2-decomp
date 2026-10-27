// ObjectClass *InfantryTypeClass::unknown_slot35(HouseClass *house) const (0x00509EF0)
// A new infantry unit of this type for the house (RA1: Create_One_Of).
#include "shared/infantry_type.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0InfantryClass@@QAE@PAVInfantryTypeClass@@PAVHouseClass@@@Z=004ff640

ObjectClass *InfantryTypeClass::unknown_slot35(HouseClass *house) const
{
    return (ObjectClass *)new InfantryClass((InfantryTypeClass *)this, house);
}
