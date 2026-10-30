// int BuildingTypeClass::unknown_func_45ec90() const (0x0045EC90)
// 0 for artillery; 0x40 for sensor arrays, tick tanks and ICBM launchers;
// otherwise 0x80 (flag values; meaning unknown).
#include "shared/building_type.hpp"

int BuildingTypeClass::unknown_func_45ec90() const
{
    if (!SensorArray && !TickTank && !ICBMLauncher && !Artillary) {
        return 0x80;
    }
    if (Artillary) {
        return 0;
    }
    if (SensorArray || TickTank || ICBMLauncher) {
        return 0x40;
    }
    return 0x80;
}

#include "shared/building_foundation_tables.hpp"
