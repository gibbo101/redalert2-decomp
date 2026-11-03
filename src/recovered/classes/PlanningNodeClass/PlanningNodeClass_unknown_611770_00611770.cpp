#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611770() (0x00611770)
// For each member whose path loops back to this node (Node_Index == the
// token's LoopStart), marks the member (+0x0C) and counts it on the node's own
// branch, which takes the event of the member's last node on the first count;
// then records in +0xB0 the branch whose event lies at the coordinate of that
// loop event (-1 if none). Names are hypotheses. The token is fetched again for
// Last_Node; the loop event is read through Get_Count/Get_Event and the branch
// event is copied into a named local before both coordinates are taken.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611770()
{
    int count = Members.Count();
    for (int index = 0; index < count; index++) {
        PlanningMemberClass *member = Members[index];
        TechnoClass *owner = member->Owner;
        PlanningTokenClass *token = Planning_Token(owner);
        if (token->Node_Index(this) == token->LoopStart) {
            member->unknown_0c = true;
            if (Branch.Increment_Count() == 1) {
                Branch.Set_Event(Planning_Token(owner)->Last_Node()->Event_For(owner));
            }
        }
    }
    unknown_b0 = -1;
    if (Branch.Get_Count() != 0) {
        int branches = Branches.Count();
        EventClass event = Branch.Get_Event();
        for (int i = 0; i < branches; i++) {
            EventClass branch_event = Branches[i]->Get_Event();
            CoordStruct coord = Planning_Event_Coord(event);
            CoordStruct branch_coord = Planning_Event_Coord(branch_event);
            if (coord == branch_coord) {
                unknown_b0 = i;
                return;
            }
        }
    }
}
