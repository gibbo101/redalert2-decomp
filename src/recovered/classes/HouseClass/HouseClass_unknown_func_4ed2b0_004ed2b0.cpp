// bool HouseClass::unknown_func_4ed2b0(WaypointClass *waypoint, int *path, char *position) (0x004ED2B0)
// Finds a waypoint in the house's waypoint paths (making missing paths).
#include "shared/techno.hpp"
#include "shared/waypoint_path.hpp"

bool HouseClass::unknown_func_4ed2b0(WaypointClass *waypoint, int *path, char *position)
{
    for (int index = 0; index < 12; index++) {
        if (WaypointPaths[index] == 0) {
            WaypointPaths[index] = new WaypointPathClass(index);
        }
        for (int point = 0; point < WaypointPaths[index]->Waypoints.Count(); point++) {
            if (WaypointPaths[index]->Get_Waypoint(point) == waypoint) {
                *path = index;
                *position = (char)point;
                return true;
            }
        }
    }
    *path = -1;
    *position = 0;
    return false;
}
