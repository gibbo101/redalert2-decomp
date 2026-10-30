// Ask the produced building type to flush its placement cells.
#include "shared/building.hpp"
// @ref ?unknown_458b10@BuildingTypeClass@@=00458b10
int BuildingClass::Flush_For_Placement_0044a3d0(TechnoClass const *object, Cell const &cell)
{
    if (object) return static_cast<BuildingTypeClass const *>(object->Class_Of())->unknown_458b10(cell, House);
    return -1;
}
