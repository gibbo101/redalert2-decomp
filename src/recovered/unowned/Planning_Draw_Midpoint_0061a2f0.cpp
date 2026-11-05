#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Midpoint(Point2D start, Point2D end, int color) (0x0061A2F0)
// When two screen points are more than 36 pixels apart, outlines a 21 x 21
// square centred on their midpoint.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

// @ref ?Length@Point2D@@QBEHXZ=0047d060
// @ref ??GPoint2D@@QBE?AU0@ABU0@@Z=0047d040
inline int Point2D::Length() const
{
    int x = X;
    int y = Y;
    return (int)unknown_sqrt_4ba410((double)y * y + (double)x * x);
}

void __fastcall Planning_Draw_Midpoint(Point2D start, Point2D end, int color)
{
    if ((start - end).Length() >= 37) {
        int x = (start.X + end.X) / 2 - 10;
        int y = (start.Y + end.Y) / 2 - 10;
        ::Rect view = Unknown_006F1F30();
        ::Rect square(x, y, 21, 21);
        unknown_surface_839964->Draw_Rect(view, square, color);
    }
}
