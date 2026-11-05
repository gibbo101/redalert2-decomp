#define RA2_COORD_EQUAL_MEMBER
// Counts one member in its existing branch, or adds the previous node's order.
#include "shared/planning.hpp"

int PlanningNodeClass::unknown_611bd0(PlanningMemberClass *member)
{
    TechnoClass *owner = member->Get_Owner();
    int index = unknown_611a80(owner);
    if (index == -1) {
        PlanningNodeClass *previous = Previous(owner);
        PlanningNodeClass *last = Planning_Token(owner)->Last_Node();
        if (previous == last) {
            member->Set_BranchIndex(-1);
            return -1;
        }
        EventClass event = previous->Event_For(owner);
        PlanningBranchClass *branch = new PlanningBranchClass;
        branch->Set_Event(event);
        branch->Increment_Count();
        Branches.Add(branch);
        int count = Branches.Count() - 1;
        if (unknown_6114e0())
            unknown_611fd0();
        unknown_612b50(false);
        member->Set_BranchIndex(count);
        return count;
    } else {
        PlanningBranchClass *branch = Branches[index];
        branch->Set_unknown_74(-1);
        unknown_612b50(false);
        branch->Increment_Count();
        member->Set_BranchIndex(index);
        return index;
    }
}
