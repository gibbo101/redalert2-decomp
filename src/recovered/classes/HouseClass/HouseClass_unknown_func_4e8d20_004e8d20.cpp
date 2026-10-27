// int HouseClass::unknown_func_4e8d20() (0x004E8D20)
// 4 when the house has buildings but none whose type sets +0xC44; else 0.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

int HouseClass::unknown_func_4e8d20()
{
    if (unknown_198 != 3 && CurBuildings > 0) {
        int count = Buildings.Count();
        for (int index = 0; index < count; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
            if (building != 0 && building->unknown_7d && !building->unknown_76 &&
                ((UnknownBuildingTypeView *)building->Type)->unknown_c44 != 0) {
                return 0;
            }
        }
        return 4;
    }
    return 0;
}
