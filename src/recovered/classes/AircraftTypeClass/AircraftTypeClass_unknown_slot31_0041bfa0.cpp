// CoordStruct AircraftTypeClass::unknown_slot31() const (0x0041BFA0)
// One cell square, twice the 0x0083C550 height.
#include "shared/aircraft_type.hpp"
// @ref ?unknown_83c550@@3HA=0083c550

CoordStruct AircraftTypeClass::unknown_slot31() const
{
    return CoordStruct(256, 256, unknown_83c550 * 2);
}
