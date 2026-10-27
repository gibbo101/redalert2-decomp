#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Add_Member(TechnoClass *techno, EventClass const &event) (0x00610D60)
#include "shared/planning.hpp"

void PlanningNodeClass::Add_Member(TechnoClass *techno, EventClass const &event)
{
    PlanningMemberClass *member = new PlanningMemberClass;
    member->Owner = techno;
    EventClass *copy = new EventClass;
    *copy = event;
    member->Event = copy;
    Members.Add(member);
    PlanningTokenClass *token = Planning_Token(techno);
    token->Nodes.Add(this);
    if (token->unknown_8c == -1) {
        token->unknown_8c = token->Nodes.Count() - 1;
    }
    unknown_611bd0(member);
}
