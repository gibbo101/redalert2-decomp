#define RA2_COORD_EQUAL_MEMBER
// Rect PlanningNodeClass::Outer_Rect() const (0x00612B90)
#include "shared/planning.hpp"

::Rect PlanningNodeClass::Outer_Rect() const
{
    ::Rect rect = Rect();
    Planning_Inflate(rect, 4);
    return rect;
}
