#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Midpoint(Point2D start, Point2D end, int color) (0x0061A2F0)
// When two screen points are more than 36 pixels apart, outlines a 21 x 21
// square centred on their midpoint.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void __fastcall Planning_Draw_Midpoint(Point2D start, Point2D end, int color)
{
    Point2D delta = start - end;
    int distance = (int)unknown_sqrt_4ba410((double)delta.Y * delta.Y + (double)delta.X * delta.X);
    if (distance >= 37) {
        ::Rect view = Unknown_006F1F30();
        ::Rect square((start.X + end.X) / 2 - 10, (start.Y + end.Y) / 2 - 10, 21, 21);
        unknown_surface_839964->Draw_Rect(view, square, color);
    }
}
