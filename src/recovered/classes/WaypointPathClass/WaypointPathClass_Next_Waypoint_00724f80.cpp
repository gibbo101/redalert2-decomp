// WaypointPathClass Next Waypoint (0x724F80)
#include "shared/waypoint_path.hpp"

WaypointClass *WaypointPathClass::Next_Waypoint(WaypointClass const *waypoint)
{
    int index = Waypoints.ID(waypoint) + 1;
    if (Selected != -1 && index == Waypoints.Count()) {
        index = Selected;
    }
    if (index >= 0 && index < Waypoints.Count()) {
        return &Waypoints[index];
    }
    return 0;
}

