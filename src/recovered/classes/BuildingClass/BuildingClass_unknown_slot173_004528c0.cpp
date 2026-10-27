// void BuildingClass::unknown_slot173() (0x004528C0, slot 173)
// Scatters (slot 87, from the zero coordinate) every active infantry whose
// cell holds this building, unless it is headed for another object.
#include "shared/building.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0

void BuildingClass::unknown_slot173()
{
    for (int index = 0; index < Infantry.Count(); index++) {
        UnknownBuildingInfantryView *infantry = (UnknownBuildingInfantryView *)Infantry[index];
        ObjectClass *building = Map[infantry->unknown_slot19(0)].unknown_4717b0();
        if (infantry->unknown_7d && building && building == this
            && (!infantry->unknown_494 || infantry->unknown_494 == building)) {
            infantry->unknown_slot87(unknown_geometry_l, 1 != 0, 1 != 0);
        }
    }
}
