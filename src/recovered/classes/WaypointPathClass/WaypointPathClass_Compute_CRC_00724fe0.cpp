// WaypointPathClass Compute CRC (0x724FE0)
#include "shared/waypoint_path.hpp"
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void WaypointPathClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)Selected);
    crc((long)Waypoints.Count());
}

