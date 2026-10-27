// Refresh all live laser-fence posts in the global building list.
#include "shared/building.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_44dfc0@BuildingClass@@QAEXH@Z=0044dfc0
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
void __fastcall BuildingClass::unknown_44df40()
{
    for(int index=0;index<unknown_BuildingClass_list_00a40af8.Count();++index) {
        BuildingClass *building=unknown_BuildingClass_list_00a40af8[index];
        if(building && building->Type->LaserFencePost && unknown_a40774==0 && building->unknown_7d && !building->unknown_76) {
            building->unknown_44dfc0(0);
            building->unknown_44dfc0(2);
            building->unknown_44dfc0(4);
            building->unknown_44dfc0(6);
            building->unknown_44e5a0(1);
        }
    }
}
