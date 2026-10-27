// WaypointPathClass Get Waypoint (0x724D60)
#include "shared/waypoint_path.hpp"

WaypointClass *WaypointPathClass::Get_Waypoint(int index)
{
    if (index >= 0 && index < Waypoints.Count()) {
        return &Waypoints[index];
    }
    return 0;
}

