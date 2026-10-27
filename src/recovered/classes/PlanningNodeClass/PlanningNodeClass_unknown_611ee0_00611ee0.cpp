#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611ee0() (0x00611EE0)
// Resets the node's branches: deletes them all and takes every member out
// of its branch and the loop branch.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611ee0()
{
    int branches = Branches.Count();
    for (int b = 0; b < branches; b++) {
        delete Branches[b];
    }
    Branches.Clear();
    int members = Members.Count();
    for (int m = 0; m < members; m++) {
        PlanningMemberClass *member = Members[m];
        member->BranchIndex = -1;
        member->unknown_0c = false;
    }
    Branch.Clear_Count();
    unknown_b0 = -1;
}
