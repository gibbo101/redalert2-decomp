#define RA2_COORD_EQUAL_MEMBER
// void __stdcall Planning_Mouse_Down(int x, int y) (0x00617860)
// The mouse button went down: remembers the screen point when planning mode
// is on and nothing is selected.
#include "shared/planning.hpp"
// @ref ?unknown_flag_a76770@@3_NA=00a76770
// @ref ?unknown_point_a76728@@3UPoint2D@@A=00a76728
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4

void __stdcall Planning_Mouse_Down(int x, int y)
{
    unknown_flag_a76770 = true;
    unknown_point_a76728 = Point2D(-1, -1);
    if (unknown_flag_a767a4 && unknown_objects_a40c60.Count() <= 0) {
        unknown_point_a76728 = Point2D(x, y);
    }
}
