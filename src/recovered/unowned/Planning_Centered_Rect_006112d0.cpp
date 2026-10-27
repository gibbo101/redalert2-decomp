#define RA2_COORD_EQUAL_MEMBER
// Rect __fastcall Planning_Centered_Rect(int size, Point2D center) (0x006112D0)
#include "shared/planning.hpp"

Rect __fastcall Planning_Centered_Rect(int size, Point2D center)
{
    int half = -(size / 2);
    Point2D corner = center;
    corner.X += half;
    corner.Y += half;
    return Rect(corner.X, corner.Y, size, size);
}
