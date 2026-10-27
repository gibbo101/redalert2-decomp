// Power on the building, refresh its house and resume powered animations.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
// @ref ?unknown_44f8e0@BuildingClass@@QAEXXZ=0044f8e0
// @ref ?unknown_537540@UnknownBuilding4E8@@QAEXH@Z=00537540
// @ref ?unknown_func_422c20@AnimClass@@QAEXXZ=00422c20
// @ref ?unknown_func_4f3170@HouseClass@@QAEXH_NH@Z=004f3170
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ??_C@_0BD@BHPD@EVA_BuildingOnLine?$AA@=007cfa58
// @ref ?Unknown_00715B40@@YIXPBDHH@Z=00715b40
void BuildingClass::unknown_44d3e0()
{
    if(!unknown_530 && unknown_3fc==0) {
        unknown_530=true;
        unknown_75=true;
        House->unknown_5668=true;
        House->unknown_5669=true;
        House->unknown_144=true;
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
        for(int anim=0;anim<18;++anim) {
            if(Type->Anims[anim].Powered && unknown_454[anim])
                ((AnimClass *)unknown_454[anim])->unknown_func_422c20();
        }
        if(Type->Factory) House->unknown_func_4f3170(Type->Factory,Type->Naval,0);
        if(House->Unknown_004F52B0()) Unknown_00715B40("EVA_BuildingOnLine",-1,-1);
    }
}
