#define RA2_COORD_EQUAL_MEMBER
// CoordStruct PlanningBranchClass::Coord() const (0x00610950)
#include "shared/planning.hpp"

CoordStruct PlanningBranchClass::Coord() const
{
    CoordStruct coord = Planning_Event_Coord(Event);
    return coord;
}
