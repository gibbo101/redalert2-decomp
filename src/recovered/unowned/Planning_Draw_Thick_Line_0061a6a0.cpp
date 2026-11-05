#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Thick_Line(Point2D start, Point2D end, int thickness, int color) (0x0061A6A0)
// Draws thickness solid lines side by side, centred on the line from start to end.
#include "shared/planning.hpp"

void __fastcall Planning_Draw_Thick_Line(Point2D start, Point2D end, int thickness, int color)
{
    int last = thickness / 2;
    for (int offset = last - thickness + 1; offset <= last; offset++) {
        Planning_Draw_Line(start, end, offset, color, false);
    }
}
