// WaypointPathClass Set Waypoint (0x724ED0)
#include "shared/waypoint_path.hpp"

void WaypointPathClass::Set_Waypoint(int index, WaypointClass const &waypoint)
{
    if (index >= 0 && index < Waypoints.Count()) {
        new (&Waypoints[index]) WaypointClass(waypoint);
    }
}

