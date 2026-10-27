// BuildingClass *HouseClass::unknown_func_4e5160() (0x004E5160)
// The building with tiberium storage that has the most free room.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

BuildingClass *HouseClass::unknown_func_4e5160()
{
    UnknownBuildingView *best = 0;
    float best_room = 0;
    int count = Buildings.Count();
    for (int index = 0; index < count; index++) {
        UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
        if (building != 0 && building->unknown_74) {
            int storage = ((UnknownBuildingTypeView *)building->Type)->Storage;
            if (storage > 0) {
                float capacity = (float)storage;
                float room = capacity - ((StorageClass *)&building->unknown_294)->Get_Total_Amount();
                if (best == 0 || room > best_room) {
                    best_room = room;
                    best = building;
                }
            }
        }
    }
    return (BuildingClass *)best;
}
