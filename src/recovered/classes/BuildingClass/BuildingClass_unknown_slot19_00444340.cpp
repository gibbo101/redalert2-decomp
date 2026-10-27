// CoordStruct BuildingClass::unknown_slot19(TechnoClass *techno) const (0x00444340, slot 19)
// Where a techno docks: slot 41 for helipads and repair bays, otherwise
// the center.
#include "shared/building.hpp"

CoordStruct BuildingClass::unknown_slot19(TechnoClass *techno) const
{
    if (Type->Helipad) {
        return unknown_slot41((int)techno);
    }
    if (Type->UnitRepair) {
        return unknown_slot41((int)techno);
    }
    return Center_Coord();
}
