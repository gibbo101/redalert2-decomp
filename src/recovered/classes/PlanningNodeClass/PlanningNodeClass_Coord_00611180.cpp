#define RA2_COORD_EQUAL_MEMBER
// CoordStruct PlanningNodeClass::Coord() const (0x00611180)
#include "shared/planning.hpp"

CoordStruct PlanningNodeClass::Coord() const
{
    CoordStruct coord = Planning_Event_Coord(*Members[0]->Event);
    return coord;
}
