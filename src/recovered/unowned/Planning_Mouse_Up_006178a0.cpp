#define RA2_COORD_EQUAL_MEMBER
// void __stdcall Planning_Mouse_Up(int x, int y) (0x006178A0)
// A click (the button came up within 4 pixels of where it went down) forgets
// the remembered node.
#include "shared/planning.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_flag_a76770@@3_NA=00a76770
// @ref ?unknown_point_a76728@@3UPoint2D@@A=00a76728
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4
// @ref ?unknown_node_a766b0@@3PAVPlanningNodeClass@@A=00a766b0

void __stdcall Planning_Mouse_Up(int x, int y)
{
    unknown_flag_a76770 = false;
    if (unknown_flag_a767a4 && unknown_objects_a40c60.Count() <= 0 && unknown_node_a766b0
        && abs(x - unknown_point_a76728.X) <= 3 && abs(y - unknown_point_a76728.Y) <= 3) {
        unknown_node_a766b0 = 0;
    }
}
