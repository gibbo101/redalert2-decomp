#define RA2_COORD_EQUAL_MEMBER
// ::Rect PlanningNodeClass::Outer_Rect2() const (0x00612C30)
// The grown node marker grown by 4 more pixels on every side.
#include "shared/planning.hpp"

::Rect PlanningNodeClass::Outer_Rect2() const
{
    ::Rect rect = Outer_Rect();
    Planning_Inflate(rect, 4);
    return rect;
}
