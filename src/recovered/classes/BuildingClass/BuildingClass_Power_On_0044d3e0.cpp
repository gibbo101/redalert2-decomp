// BuildingClass::Turn_On 0x0044D3E0 (TibSun building.cpp Turn_On): powers the building on.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_func_4f3170@HouseClass@@QAEXH_NH@Z=004f3170
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ??_C@_0BD@BHPD@EVA_BuildingOnLine?$AA@=007cfa58
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
void BuildingClass::unknown_44d3e0()
{
    if(!unknown_530 && unknown_3fc==0) {
        unknown_530=true;
        unknown_75=true;
        House->unknown_5668=true;
        House->unknown_5669=true;
        House->unknown_144=true;
        unknown_44d600();

        if(Type->Factory) {
            House->unknown_func_4f3170(Type->Factory,Type->Naval,0);
        }

        if(House->Unknown_004F52B0()) {
            Speech_Play_Name("EVA_BuildingOnLine",-1,-1);
        }
    }
}
