#define RA2_COORD_EQUAL_MEMBER
// CoordStruct PlanningNodeClass::Branch_Coord(int index) const (0x006115D0)
#include "shared/planning.hpp"

CoordStruct PlanningNodeClass::Branch_Coord(int index) const
{
    PlanningBranchClass *branch = Branches[index];
    CoordStruct coord = branch->Coord();
    return coord;
}
