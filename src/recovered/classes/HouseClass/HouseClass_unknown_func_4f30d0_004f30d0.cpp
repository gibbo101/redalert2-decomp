// int HouseClass::unknown_func_4f30d0() (0x004F30D0)
// The index of the first waypoint path of the house that has no waypoints, else -1; a path that was not
// made yet is made empty for the test (and not kept).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/waypoint_path.hpp"
// @ref ??0WaypointPathClass@@QAE@XZ=00724b10
// @ref ??2@YAPAXI@Z=00782017

int HouseClass::unknown_func_4f30d0()
{
    for (int index = 0; index < 12; index++) {
        WaypointPathClass *path = WaypointPaths[index];
        if (path == 0) {
            path = new WaypointPathClass;
        }
        if (path->Waypoints.Count() == 0) {
            return index;
        }
    }
    return -1;
}
