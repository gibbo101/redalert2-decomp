// WaypointClass *HouseClass::unknown_func_4ed200(Cell const &cell) (0x004ED200)
// The waypoint of any path in the cell, else 0 (making missing
// paths).
#include "shared/techno.hpp"
#include "shared/waypoint_path.hpp"

WaypointClass *HouseClass::unknown_func_4ed200(Cell const &cell)
{
    for (int index = 0; index < 12; index++) {
        if (WaypointPaths[index] == 0) {
            WaypointPaths[index] = new WaypointPathClass(index);
        }
        for (int point = 0; point < WaypointPaths[index]->Waypoints.Count(); point++) {
            WaypointClass *waypoint = WaypointPaths[index]->Get_Waypoint(point);
            if (Coord_Cell(waypoint->Coord) == cell) {
                return waypoint;
            }
        }
    }
    return 0;
}
