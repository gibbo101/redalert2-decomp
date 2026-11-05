#define RA2_COORD_EQUAL_MEMBER
// Point2D PlanningNodeClass::Pixel() const (0x006111C0)
#include "shared/planning.hpp"

Point2D PlanningNodeClass::Pixel() const
{
    CoordStruct coord = Coord();
    Point2D pixel = Planning_Coord_Pixel(coord);
    return pixel;
}
