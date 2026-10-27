// int BuildingClass::unknown_slot45() const (0x00445380, slot 45)
// The object value, raised by 32 for type flag +0x135F and lowered by 16
// for type flag +0x1351.
#include "shared/building.hpp"
// @ref ?unknown_slot45@ObjectClass@@UBEHXZ=005d5450

int BuildingClass::unknown_slot45() const
{
    int value = ObjectClass::unknown_slot45();
    return value + ((Type->TurretAnimIsVoxel ? 32 : 0) - (Type->Gate ? 16 : 0));
}
