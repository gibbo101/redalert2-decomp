#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_612ec0() (0x00612EC0)
// Drops the whole path: takes the owner out of every node (nodes left empty
// delete themselves), unlists the owner and forgets the loop.
#include "shared/planning.hpp"
// @ref ?Clear@?$VectorClass@PAVPlanningMemberClass@@@@UAEXXZ=0061abf0

void PlanningTokenClass::unknown_612ec0()
{
    int count = Nodes.Count();
    bool none = count == 0;
    for (int i = 0; i < count; i++) {
        PlanningNodeClass *node = Nodes[i];
        node->Remove_Member(Owner);
    }
    if (!none) {
        Planning_Unlist_Techno(Owner);
    }
    Nodes.Clear();
    unknown_8c = -1;
    LoopLength = -1;
    LoopStart = -1;
    unknown_98 = false;
    unknown_99 = false;
}
