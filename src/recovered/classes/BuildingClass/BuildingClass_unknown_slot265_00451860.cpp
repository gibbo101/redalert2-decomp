// void BuildingClass::unknown_slot265() (0x00451860, slot 265)
// Calls the map's Unknown_00631AF0 for each foundation offset of the type, then sets
// unknown_37b to false.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006328D0@RadarClass@@QAEPAV?$DynamicVectorClass@UPoint2D@@@@PAVBuildingTypeClass@@@Z=006328d0

void BuildingClass::unknown_slot265()
{
    DynamicVectorClass<Point2D> *offsets = Map.Unknown_006328D0(Type);
    for (int index = 0; index < offsets->Count(); index++) {
        Map.Unknown_00631AF0(this, Point_Sum((*offsets)[index], unknown_cell_1a0()));
    }
    unknown_37b = false;
}
