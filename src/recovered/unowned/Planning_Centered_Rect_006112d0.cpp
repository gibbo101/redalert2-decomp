#define RA2_COORD_EQUAL_MEMBER
// Rect __fastcall Planning_Centered_Rect(int size, Point2D center) (0x006112D0)
#include "shared/planning.hpp"
// The corner and size are named before the Rect is built (field locals); this
// larger body keeps the call out of line where Rect() sits two inline levels
// deep (Is_At_Pixel, Outer_Rect2, Draw_All) and inlined in Rect(), Outer_Rect()
// and Fill_Marker, as in the original.

Rect __fastcall Planning_Centered_Rect(int size, Point2D center)
{
    int half = -(size / 2);
    Point2D corner = center;
    corner.X += half;
    corner.Y += half;
    int x = corner.X;
    int y = corner.Y;
    int width = size;
    int height = size;
    Rect rect(x, y, width, height);
    return rect;
}
