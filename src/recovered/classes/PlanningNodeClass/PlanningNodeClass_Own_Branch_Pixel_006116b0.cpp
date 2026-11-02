#define RA2_COORD_EQUAL_MEMBER
// Point2D PlanningNodeClass::Own_Branch_Pixel() const (0x006116B0)
// The screen pixel of the node's own branch event.
#include "shared/planning.hpp"

Point2D PlanningNodeClass::Own_Branch_Pixel() const
{
    return Branch.Pixel();
}
