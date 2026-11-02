#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611e20(PlanningMemberClass *member) (0x00611E20)
// Takes a member out of its branches: out of the loop branch (0x00611FA0),
// then drops its count from the branch it was filed under (forgetting the
// node's computed index); the last member out queues the node.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611e20(PlanningMemberClass *member)
{
    if (member->unknown_0c) {
        unknown_611fa0(member);
    }
    if (member->BranchIndex != -1) {
        PlanningBranchClass *branch = Branches[member->BranchIndex];
        branch->unknown_74 = -1;
        unknown_612b50(false);
        if (--branch->Count == 0) {
            Planning_Queue_Node(this);
        }
    }
    member->BranchIndex = -1;
}
