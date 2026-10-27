// void BuildingClass::unknown_slot266() (0x004518C0, slot 266)
// Passes each foundation cell of the type (offset by unknown_1a0/1a4) to
// the map's Unknown_00632620.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006328D0@RadarClass@@QAEPAV?$DynamicVectorClass@UPoint2D@@@@PAVBuildingTypeClass@@@Z=006328d0

void BuildingClass::unknown_slot266()
{
    DynamicVectorClass<Point2D> *offsets = Map.Unknown_006328D0(Type);
    for (int index = 0; index < offsets->Count(); index++) {
        Point2D cell;
        cell = Point_Sum((*offsets)[index], unknown_cell_1a0());
        Map.Unknown_00632620(cell);
    }
}
