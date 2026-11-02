#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::Copy_Nodes_To(TechnoClass *techno, int start, int count) (0x00613550)
// Adds the nodes start..start+count-1 of this path to techno's path: each
// node gets a member for techno with a copy of this owner's order there,
// aimed at techno (Planning_Copy_Members 0x006167F0 per node).
#include "shared/planning.hpp"

void PlanningTokenClass::Copy_Nodes_To(TechnoClass *techno, int start, int count)
{
    if (Planning_Token(techno) == 0) {
        return;
    }
    for (int i = start; i < start + count; i++) {
        PlanningNodeClass *node = Nodes[i];
        TechnoClass *owner = Owner;
        PlanningMemberClass *source = node->Member_For(owner);
        EventClass event = *source->Event;
        event.TargetAt(0x07) = TargetClass(techno);
        PlanningMemberClass *member = new PlanningMemberClass;
        member->Owner = techno;
        EventClass *copy = new EventClass;
        *copy = event;
        member->Event = copy;
        node->Members.Add(member);
        PlanningTokenClass *token = Planning_Token(techno);
        token->Nodes.Add(node);
        if (token->unknown_8c == -1) {
            token->unknown_8c = token->Nodes.Count() - 1;
        }
        node->unknown_611bd0(member);
    }
}
