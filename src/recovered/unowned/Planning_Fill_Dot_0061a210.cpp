#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Fill_Dot(Point2D center, int color) (0x0061A210)
// Fills the inside of a 6 x 6 square centred on a screen point.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void __fastcall Planning_Fill_Dot(Point2D center, int color)
{
    Point2D point = center;
    ::Rect view;
    view = Unknown_006F1F30();
    ::Rect square;
    square = Planning_Centered_Rect(point, 6);
    Planning_Inflate(square, -1);
    Surface *surface = unknown_surface_839964;
    surface->Fill_Rect(view, square, color);
}
