// Toggle primary factory selection within the house's factory and naval group.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ??_C@_0BM@POLG@EVA_PrimaryBuildingSelected?$AA@=007cf8a4
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
bool BuildingClass::unknown_slot287()
{
    if(Type->Factory) {
        if(unknown_32b) unknown_32b=false;
        else {
            int count=House->Buildings.Count();
            for(int index=0;index<count;++index) {
                BuildingClass *building=House->Buildings[index];
                if(!building->unknown_76 && building->Type->Factory==Type->Factory) {
                    if((Type->Naval && building->Type->Naval) || (!Type->Naval && !building->Type->Naval))
                        building->unknown_32b=false;
                }
            }
            unknown_32b=true;
            if(House->Unknown_004F52B0()) Speech_Play_Name("EVA_PrimaryBuildingSelected",-1,-1);
        }
        unknown_slot71(2);
    }
    return unknown_32b;
}
