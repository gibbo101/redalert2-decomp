// BuildingClass *HouseClass::Find_Building(int type, int zone) (0x004E8560)
// A building of the house with this building type index, in a zone (any
// zone for -1); 0 when the house has none.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

// BuildingTypes (shared/building_type.hpp, which this unit's views keep it from including).
extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;       // 0x00A35CD8

// (UnknownBuildingView: HouseClass_Silo_Redraw_Check_004e5460.cpp.)

BuildingClass *HouseClass::Find_Building(int type, int zone)
{
    if (unknown_5420.unknown_func_491d10(type) > 0) {
        int count = Buildings.Count();
        for (int index = 0; index < count; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
            if (building != 0 && !building->unknown_76 &&
                BuildingTypes.ID(building->Type) == type) {
                if (zone == -1) {
                    return (BuildingClass *)building;
                }
                if (Which_Zone(building->Center_Coord()) == zone) {
                    return (BuildingClass *)building;
                }
            }
        }
    }
    return 0;
}
