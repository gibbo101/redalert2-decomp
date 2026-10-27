// WaypointPathClass Select Waypoint (0x724E30)
#include "shared/waypoint_path.hpp"

bool WaypointPathClass::Select_Waypoint(CoordStruct const &coord)
{
    for (int index = 0; index < Waypoints.Count(); index++) {
        if (Cell((short)(Waypoints[index].Coord.X / 256), (short)(Waypoints[index].Coord.Y / 256))
            == Cell((short)(coord.X / 256), (short)(coord.Y / 256))) {
            Selected = index;
            return true;
        }
    }
    return false;
}

