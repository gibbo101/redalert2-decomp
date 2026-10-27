// WaypointPathClass Remove Waypoint (0x724F10)
#include "shared/waypoint_path.hpp"

void WaypointPathClass::Remove_Waypoint(int index)
{
    if (index >= 0 && index < Waypoints.Count()) {
        if (index == Selected || index == Waypoints.Count() - 1) {
            Selected = -1;
        }
        Waypoints.Delete(index);
    }
}

