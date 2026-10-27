// void FootClass::unknown_slot99(int path, char waypoint) (0x004CB060)
// Follows one of the player's waypoint paths (+0x418) from a waypoint
// (+0x576): the next cell is that waypoint's (+0x420); -1 clears it.
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/waypoint_path.hpp"
// @ref ??_EWaypointClass@@QAEPAXI@Z=0041b890
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Get_Waypoint@WaypointPathClass@@QAEPAUWaypointClass@@H@Z=00724d60

void FootClass::unknown_slot99(int path, char waypoint)
{
    if (path != -1) {
        unknown_418 = path;
        unknown_576 = waypoint;
        unknown_420 = Coord_Cell(unknown_player_a35db4->WaypointPaths[path]->Get_Waypoint(waypoint)->Coord);
    } else {
        unknown_418 = -1;
        unknown_576 = 0;
        unknown_420 = Cell(0, 0);
    }
    unknown_41c = Cell(0, 0);
}
