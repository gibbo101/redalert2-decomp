// void HouseClass::unknown_func_4ecfb0(CoordStruct const &coord) (0x004ECFB0)
// Adds a waypoint at a coordinate to the current path (+0x154) unless
// another path already has a waypoint in that cell (the test of
// 0x004ED140, written out here).
// @ref ?Add_Waypoint@WaypointPathClass@@QAE_NABUCoordStruct@@@Z=00724d80
#include "shared/techno.hpp"
#include "shared/waypoint_path.hpp"

void HouseClass::unknown_func_4ecfb0(CoordStruct const &coord)
{
    Cell cell = Coord_Cell(coord);
    for (int index = 0; index < 12; index++) {
        if (WaypointPaths[index] == 0) {
            WaypointPaths[index] = new WaypointPathClass(index);
        }
        for (int point = 0; point < WaypointPaths[index]->Waypoints.Count(); point++) {
            WaypointClass *waypoint = WaypointPaths[index]->Get_Waypoint(point);
            if (Coord_Cell(waypoint->Coord) == cell && index != unknown_154) {
                return;
            }
        }
    }
    Make_Waypoint_Path(unknown_154);
    WaypointPaths[unknown_154]->Add_Waypoint(coord);
}
