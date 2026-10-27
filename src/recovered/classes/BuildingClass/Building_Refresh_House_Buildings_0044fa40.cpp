// Refresh the live buildings in a house's captured building list.
// Free fastcall versus original class-owned static/member spelling remains unproved.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
// @ref ?unknown_44f8e0@BuildingClass@@QAEXXZ=0044f8e0
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house)
{
    int count = house->Buildings.Count();
    for (int index = 0; index < count; ++index) {
        BuildingClass *building = house->Buildings[index];
        if (building->unknown_7d && !building->unknown_76) {
            if (building->Type->LaserFencePost)
                building->unknown_44e5a0(0);
            building->unknown_44f8e0();
        }
    }
}
