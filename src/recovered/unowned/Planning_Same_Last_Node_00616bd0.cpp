#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Same_Last_Node(PlanningTokenClass *token1, PlanningTokenClass *token2) (0x00616BD0)
// Whether two planning tokens end at the same node: both empty (or null), or
// each one's last node holds the other's owner. Name hypothesis.
#include "shared/planning.hpp"

bool __fastcall Planning_Same_Last_Node(PlanningTokenClass *token1, PlanningTokenClass *token2)
{
    if (token1 == 0 && token2 == 0) {
        return true;
    }
    int count1 = 0;
    if (token1 != 0) {
        count1 = token1->Nodes.Count();
    }
    int count2 = 0;
    if (token2 != 0) {
        count2 = token2->Nodes.Count();
    }
    if (count1 == 0 && count2 == 0) {
        return true;
    }
    if (count1 == 0 || count2 == 0) {
        return false;
    }
    PlanningNodeClass *last1 = token1->Node_At(count1 - 1);
    PlanningNodeClass *last2 = token2->Node_At(count2 - 1);
    TechnoClass *owner1 = token1->Owner;
    TechnoClass *owner2 = token2->Owner;
    if (!last1->Has_Member(owner2)) {
        return false;
    }
    if (!last2->Has_Member(owner1)) {
        return false;
    }
    return true;
}
