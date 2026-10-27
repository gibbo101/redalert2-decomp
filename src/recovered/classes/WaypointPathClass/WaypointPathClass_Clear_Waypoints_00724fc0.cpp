// WaypointPathClass Clear Waypoints (0x724FC0)
#include "shared/waypoint_path.hpp"

void WaypointPathClass::Clear_Waypoints()
{
    Waypoints.Clear();
    Selected = -1;
}

