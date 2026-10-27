// bool UnitClass::unknown_slot31() (0x00709A00, slot 31)
// True unless the type is NonVehicle.
#include "shared/unit.hpp"

bool UnitClass::unknown_slot31()
{
    return !Type->NonVehicle;
}
