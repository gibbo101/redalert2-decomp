#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Copy_Members(PlanningNodeClass *node, PlanningNodeClass *from, EventClass event) (0x006167F0)
// Adds every member of one node to another, each with a copy of the event
// aimed at that member's techno.
#include "shared/planning.hpp"

void __fastcall Planning_Copy_Members(PlanningNodeClass *node, PlanningNodeClass *from, EventClass event)
{
    int count = from->Members.Count();
    for (int i = 0; i < count; i++) {
        TechnoClass *techno = from->Members[i]->Owner;
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
