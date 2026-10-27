// bool AircraftClass::unknown_slot31() (0x0041B040, slot 31)
// Answers slot 20 (a tail call through the vtable).
#include "shared/aircraft.hpp"

bool AircraftClass::unknown_slot31()
{
    return unknown_slot20();
}
