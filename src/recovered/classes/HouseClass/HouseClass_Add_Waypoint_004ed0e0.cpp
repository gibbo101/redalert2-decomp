// void HouseClass::Add_Waypoint(CoordStruct const &coord) (0x004ED0E0)
// Makes the current path (+0x154) and selects the waypoint at the
// coordinate in it (WaypointPathClass::Select_Waypoint 0x00724E30).
#include "shared/techno.hpp"
#include "shared/waypoint_path.hpp"

void HouseClass::Add_Waypoint(CoordStruct const &coord)
{
    Make_Waypoint_Path(unknown_154);
    WaypointPaths[unknown_154]->Select_Waypoint(coord);
}
