#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Fill_Dot(int color, int unused, int x, int y) (0x0061A210)
// Fills the inside of a 6 x 6 square centred on a screen point.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void __fastcall Planning_Fill_Dot(int color, int unused, int x, int y)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect square = Planning_Centered_Rect(6, Point2D(x, y));
    square.X += 1;
    square.Y += 1;
    square.Width -= 2;
    square.Height -= 2;
    unknown_surface_839964->Fill_Rect(view, square, color);
}
