// Building-family nearby radio-acceptor search; free/static spelling remains a hypothesis.
// Genuine local-static maximum/guard retain original storage; actual generated-name bindings are audited separately.
// @ref _?maximum@?1??Building_Find_Nearby_Radio_Acceptor_00450f90@@YIPAVBuildingClass@@PAVHouseClass@@PAVTechnoClass@@@Z@4HA=0084ecec
// @ref _?$S80@?1??Building_Find_Nearby_Radio_Acceptor_00450f90@@YIPAVBuildingClass@@PAVHouseClass@@PAVTechnoClass@@@Z@4EA=0084ed48
// @ref __real@8@4003a000000000000000=0079d150
// PRIVATE free-function ownership and selection name hypotheses.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/unknown_geometry.hpp"
BuildingClass *__fastcall Building_Find_Nearby_Radio_Acceptor_00450f90(HouseClass *house,TechnoClass *target)
{
    BuildingClass *selected=0;
    int best=0x7fffffff;
    static int maximum=(int)(unknown_geometry_diagonal*20.0);
    int count=house->unknown_80.Count();
    for(int index=0;index<count;++index) {
        BuildingClass *building=house->unknown_80[index];
        if(target->unknown_slot150(15,building)) {
            CoordStruct from=target->Coord;
            CoordStruct to=building->Coord;
            CoordStruct delta((int)((unsigned int)to.X-(unsigned int)from.X),
                              (int)((unsigned int)to.Y-(unsigned int)from.Y),
                              (int)((unsigned int)to.Z-(unsigned int)from.Z));
            double y=delta.Y,z=delta.Z,x=delta.X;
            int distance=(int)unknown_sqrt_4ba410(x*x+y*y+z*z);
            if(distance<best && distance<maximum) {selected=building;best=distance;}
        }
    }
    return selected;
}
