// void BuildingClass::unknown_44ab00() (0x0044AB00)
// Recomputes the house's flags (+0x5414): the OR of the +0x1A8 of each of
// its buildings that has a Radar type and is not selected out (+0x76
// clear); then flags the screen for a redraw.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0

void BuildingClass::unknown_44ab00()
{
    House->unknown_5414 = 0;
    int count = House->Buildings.Count();
    for (int index = 0; index < count; index++) {
        BuildingClass *building = House->Buildings[index];
        if (building && !building->unknown_76 && building->Type->Radar) {
            House->unknown_5414 |= building->unknown_1a8;
        }
    }
    Map.GScreenClass::Flag_To_Redraw(2);
}
