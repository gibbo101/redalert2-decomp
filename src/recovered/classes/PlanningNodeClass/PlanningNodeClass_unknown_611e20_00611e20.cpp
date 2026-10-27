#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611e20(PlanningMemberClass *member) (0x00611E20)
// Takes a member out of its branch: clears its loop flag (the last one
// resets the loop branch index), then drops its count from the branch it
// was filed under; the last member out queues the node.
#include "shared/planning.hpp"

// 0x00614650, expanded here.
static inline void Queue_Node(PlanningNodeClass *node)
{
    if (node != 0 && !node->IsQueued) {
        node->IsQueued = true;
        PlanningNodeClass::unknown_list_00a76758.Add(node);
    }
}

void PlanningNodeClass::unknown_611e20(PlanningMemberClass *member)
{
    if (member->unknown_0c) {
        member->unknown_0c = false;
        if (--Branch.Count == 0) {
            unknown_b0 = -1;
        }
    }
    if (member->BranchIndex != -1) {
        PlanningBranchClass *branch = Branches[member->BranchIndex];
        branch->unknown_74 = -1;
        unknown_b4 = -1;
        if (--branch->Count == 0) {
            Queue_Node(this);
        }
    }
    member->BranchIndex = -1;
}
