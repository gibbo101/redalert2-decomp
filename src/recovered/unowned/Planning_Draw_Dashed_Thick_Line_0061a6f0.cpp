#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Dashed_Thick_Line(Point2D start, Point2D end, int thickness, int color) (0x0061A6F0)
// Draws thickness - 2 dashed lines side by side (one at least), centred on the line from start to end.
#include "shared/planning.hpp"

void __fastcall Planning_Draw_Dashed_Thick_Line(Point2D start, Point2D end, int thickness, int color)
{
    int count = thickness - 2;
    int first;
    int last;
    if (count <= 0) {
        first = 0;
        last = 0;
    } else {
        last = count / 2;
        first = last - count + 1;
    }
    for (int offset = first; offset <= last; offset++) {
        Planning_Draw_Line(start, end, offset, color, true);
    }
}
