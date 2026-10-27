// void HouseClass::Make_Waypoint_Path(int index) (0x004EE8A0)
#include "shared/techno.hpp"

void HouseClass::Make_Waypoint_Path(int index)
{
    if (WaypointPaths[index] == 0) {
        WaypointPaths[index] = new WaypointPathClass(index);
    }
}
