#define RA2_COORD_EQUAL_MEMBER
// PlanningBranchClass *PlanningNodeClass::Branch_For(TechnoClass *techno) const (0x00611570)
#include "shared/planning.hpp"

PlanningBranchClass *PlanningNodeClass::Branch_For(TechnoClass *techno) const
{
    int index = Member_For(techno)->BranchIndex;
    PlanningBranchClass *branch = 0;
    if (index != -1) {
        branch = Branches[index];
    }
    return branch;
}
