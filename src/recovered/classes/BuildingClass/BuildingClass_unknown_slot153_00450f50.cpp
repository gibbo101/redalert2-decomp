// bool BuildingClass::unknown_slot153() (0x00450F50, slot 153)
// True for type values 40, 16 and 3 at +0xC44 or either type flag +0x134B,
// +0x1349.
#include "shared/building.hpp"

bool BuildingClass::unknown_slot153()
{
    int value = Type->Factory;
    if (value == 40 || value == 16 || value == 3 || Type->Cloning || Type->UnitRepair) {
        return true;
    }
    return false;
}
