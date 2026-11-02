#define RA2_COORD_EQUAL_MEMBER
// Point2D PlanningNodeClass::Branch_Pixel(int index) const (0x00611640)
// The screen pixel of a branch event.
#include "shared/planning.hpp"

Point2D PlanningNodeClass::Branch_Pixel(int index) const
{
    return Branches[index]->Pixel();
}
