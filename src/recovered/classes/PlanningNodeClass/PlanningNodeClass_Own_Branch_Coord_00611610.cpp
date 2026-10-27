#define RA2_COORD_EQUAL_MEMBER
// CoordStruct PlanningNodeClass::Own_Branch_Coord() const (0x00611610)
#include "shared/planning.hpp"

CoordStruct PlanningNodeClass::Own_Branch_Coord() const
{
    CoordStruct coord = Planning_Event_Coord(Branch.Event);
    return coord;
}
