// bool HouseClass::unknown_func_4ed140(Cell const &cell) (0x004ED140)
// False when a waypoint path other than the current one (+0x154) has a
// waypoint in the cell (making missing paths).
#include "shared/techno.hpp"
#include "shared/waypoint_path.hpp"

bool HouseClass::unknown_func_4ed140(Cell const &cell)
{
    for (int index = 0; index < 12; index++) {
        if (WaypointPaths[index] == 0) {
            WaypointPaths[index] = new WaypointPathClass(index);
        }
        for (int point = 0; point < WaypointPaths[index]->Waypoints.Count(); point++) {
            WaypointClass *waypoint = WaypointPaths[index]->Get_Waypoint(point);
            if (Coord_Cell(waypoint->Coord) == cell && index != unknown_154) {
                return false;
            }
        }
    }
    return true;
}
