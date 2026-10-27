// ObjectClass *AircraftTypeClass::unknown_slot35(HouseClass *house) const (0x0041BED0)
// A new aircraft of this type for the house (RA1: Create_One_Of).
#include "shared/aircraft_type.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AircraftClass@@QAE@PAVAircraftTypeClass@@PAVHouseClass@@@Z=00413a40

ObjectClass *AircraftTypeClass::unknown_slot35(HouseClass *house) const
{
    return (ObjectClass *)new AircraftClass((AircraftTypeClass *)this, house);
}
