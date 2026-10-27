// int DisplayClass::Unknown_0049EAD0(int mouse, Cell const &cell) (0x0049EAD0)
// Over a cell holding one of the player's waypoints, some mouse shapes are
// replaced (1 and 2 by 45, 3, 9 and 11 by 50, 5 and 6 by 49).
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_func_4ed200@HouseClass@@QAEPAVWaypointClass@@ABVCell@@@Z=004ed200

int DisplayClass::Unknown_0049EAD0(int mouse, Cell const &cell)
{
    if (unknown_player_a35db4->unknown_func_4ed200(cell)) {
        switch (mouse) {
        case 1:
        case 2:
            return 45;
        case 5:
        case 6:
            return 49;
        case 3:
        case 9:
        case 11:
            return 50;
        }
    }
    return mouse;
}
