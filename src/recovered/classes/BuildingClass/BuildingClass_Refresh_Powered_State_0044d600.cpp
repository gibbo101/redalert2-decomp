// BuildingClass::Power_On 0x0044D600 (TibSun building.cpp Power_On): back onto the power grid.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
// @ref ?unknown_537540@UnknownBuilding4E8@@QAEXH@Z=00537540
// @ref ?unknown_func_422c20@AnimClass@@QAEXXZ=00422c20
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);
void BuildingClass::unknown_44d600()
{
    unknown_5ba=true;
    Building_Refresh_House_Buildings_0044fa40(House);

    if(unknown_4e8) {
        unknown_4e8->Activate(0);
    }

    if(Type->LaserFencePost) {
        unknown_44e5a0(0);
    }

    int anim=0;
    do {
        if(Type->Anims[anim].Powered && unknown_454[anim])
            ((AnimClass *)unknown_454[anim])->unknown_func_422c20();
    } while(++anim<18);
}
