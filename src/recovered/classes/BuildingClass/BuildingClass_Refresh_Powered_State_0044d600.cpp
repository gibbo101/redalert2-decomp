// Refresh powered state after setting the building flag.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
// @ref ?unknown_44f8e0@BuildingClass@@QAEXXZ=0044f8e0
// @ref ?unknown_537540@UnknownBuilding4E8@@QAEXH@Z=00537540
// @ref ?unknown_func_422c20@AnimClass@@QAEXXZ=00422c20
void BuildingClass::unknown_44d600()
{
    unknown_5ba=true;
    HouseClass *house=House;
    int count=house->Buildings.Count();
    for(int index=0;index<count;++index) {
        BuildingClass *building=house->Buildings[index];
        if(building->unknown_7d && !building->unknown_76) {
            if(building->Type->LaserFencePost) building->unknown_44e5a0(0);
            building->unknown_44f8e0();
        }
    }
    if(unknown_4e8) unknown_4e8->unknown_537540(0);
    if(Type->LaserFencePost) unknown_44e5a0(0);
    int anim=0;
    do {
        if(Type->Anims[anim].Powered && unknown_454[anim])
            ((AnimClass *)unknown_454[anim])->unknown_func_422c20();
    } while(++anim<18);
}
