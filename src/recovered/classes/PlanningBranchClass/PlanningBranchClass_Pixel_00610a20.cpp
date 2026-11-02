#define RA2_COORD_EQUAL_MEMBER
// Point2D PlanningBranchClass::Pixel() const (0x00610A20)
// The screen pixel of the branch event.
#include "shared/planning.hpp"

Point2D PlanningBranchClass::Pixel() const
{
    CoordStruct coord = Coord();
    return Planning_Coord_Pixel(coord);
}
