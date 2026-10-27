// ObjectClass *BuildingTypeClass::unknown_slot35(HouseClass *house) (0x004584A0)
// A new structure of this type for the house (RA1: Create_One_Of).
#include "shared/building_view.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0BuildingClass@@QAE@PAVBuildingTypeClass@@PAVHouseClass@@@Z=00438ce0

ObjectClass *BuildingTypeClass::unknown_slot35(HouseClass *house) const
{
    return (ObjectClass *)new BuildingClass((BuildingTypeClass *)this, house);
}
