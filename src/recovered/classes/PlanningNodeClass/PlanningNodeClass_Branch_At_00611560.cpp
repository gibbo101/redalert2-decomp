#define RA2_COORD_EQUAL_MEMBER
// PlanningBranchClass *PlanningNodeClass::Branch_At(int index) const (0x00611560)
#include "shared/planning.hpp"

PlanningBranchClass *PlanningNodeClass::Branch_At(int index) const
{
    return Branches[index];
}
