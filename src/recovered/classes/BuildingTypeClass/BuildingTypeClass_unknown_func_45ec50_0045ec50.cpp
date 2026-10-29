// bool BuildingTypeClass::unknown_func_45ec50() const (0x0045EC50)
// Sensor array, tick tank, ICBM launcher or artillery. The callers test al
// (UnitClass 0x006FDFC0); the logical expression is materialized as 0/1 in eax.
#include "shared/building_type.hpp"

bool BuildingTypeClass::unknown_func_45ec50() const
{
    return SensorArray || TickTank || ICBMLauncher || Artillary;
}
