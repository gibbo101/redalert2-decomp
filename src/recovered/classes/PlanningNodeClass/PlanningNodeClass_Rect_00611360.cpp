#define RA2_COORD_EQUAL_MEMBER
// Rect PlanningNodeClass::Rect() const (0x00611360)
#include "shared/planning.hpp"

Rect PlanningNodeClass::Rect() const
{
    ::Rect rect;
    rect = Planning_Centered_Rect(Pixel(), 8);
    return rect;
}
