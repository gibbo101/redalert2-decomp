// ObjectClass *CellClass::unknown_476750() const (0x00476750): the building
// in the cell when its type is a gate (BuildingTypeClass::Gate), else null.
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"

ObjectClass *CellClass::unknown_476750() const
{
    BuildingClass *building = (BuildingClass *)unknown_4717b0();
    if (building != 0 && !building->Type->Gate) {
        building = 0;
    }
    return building;
}
