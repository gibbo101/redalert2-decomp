// Cell HouseClass::unknown_func_4f0e30(BuildingTypeClass *upgrade) (0x004F0E30)
// The building an upgrade goes on: this house's buildings of the type the
// upgrade powers up (PowersUpBuilding) that take it (0x0044D900); with
// PowersUpToLevel -1 the least upgraded one, else one without upgrades.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"

Cell HouseClass::unknown_func_4f0e30(BuildingTypeClass *upgrade)
{
    int index = BuildingTypeClass::From_Name(upgrade->PowersUpBuilding);
    if (index == -1) {
        return Cell(0, 0);
    }
    BuildingTypeClass *type = BuildingTypes[index];
    int best = type->Upgrades + 10;
    BuildingClass *chosen = 0;
    bool any_level = upgrade->PowersUpToLevel == -1;
    for (int at = 0; at < unknown_BuildingClass_list_00a40af8.Count(); at++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[at];
        if (building->House == this && building->Type == type && building->unknown_44d900(upgrade, this)) {
            if ((any_level && best > building->unknown_5c6) || (!any_level && building->unknown_5c6 == 0)) {
                best = building->unknown_5c6;
                chosen = building;
            }
        }
    }
    if (chosen != 0) {
        CoordStruct coord = chosen->Coord;
        return Coord_Cell(coord);
    }
    return Cell(0, 0);
}
