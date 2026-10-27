#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Dot(int color, int unused, int x, int y) (0x0061A190)
// Outlines a 6 x 6 square centred on a screen point.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void __fastcall Planning_Draw_Dot(int color, int unused, int x, int y)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect square = Planning_Centered_Rect(6, Point2D(x, y));
    unknown_surface_839964->Draw_Rect(view, square, color);
}
