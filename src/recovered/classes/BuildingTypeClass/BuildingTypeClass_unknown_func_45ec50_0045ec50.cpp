// int BuildingTypeClass::unknown_func_45ec50() const (0x0045EC50)
// Sensor array, tick tank, ICBM launcher or artillery.
#include "shared/building_type.hpp"

int BuildingTypeClass::unknown_func_45ec50() const
{
    if (SensorArray || TickTank || ICBMLauncher || Artillary) {
        return 1;
    }
    return 0;
}
