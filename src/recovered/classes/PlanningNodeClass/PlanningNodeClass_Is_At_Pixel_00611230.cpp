#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Is_At_Pixel(Point2D point) const (0x00611230)
// Whether a screen point lies inside the grown node marker.
#include "shared/planning.hpp"

int PlanningNodeClass::Is_At_Pixel(Point2D point) const
{
    ::Rect rect = Outer_Rect();
    if (rect.Is_Point_Within(point)) {
        return 1;
    }
    return 0;
}
