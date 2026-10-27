// bool AircraftTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x0041BF90)
// Aircraft are never placed this way (RA1: Create_And_Place).
#include "shared/aircraft_type.hpp"

bool AircraftTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    return false;
}
