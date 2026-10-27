// void FootClass::unknown_slot194() (0x004CCDF0)
// Following a waypoint path (+0x418, the player's path index; +0x576, the
// waypoint index): heads for the waypoint after the current one.
#include "shared/foot.hpp"
#include "shared/waypoint_path.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Get_Waypoint@WaypointPathClass@@QAEPAUWaypointClass@@H@Z=00724d60
// @ref ?unknown_4cb110@FootClass@@QAEXPAUWaypointClass@@@Z=004cb110

void FootClass::unknown_slot194()
{
    if (unknown_418 != -1) {
        unknown_4cb110(unknown_player_a35db4->WaypointPaths[unknown_418]->Next_Waypoint(
            unknown_player_a35db4->WaypointPaths[unknown_418]->Get_Waypoint(unknown_576)));
    }
}
