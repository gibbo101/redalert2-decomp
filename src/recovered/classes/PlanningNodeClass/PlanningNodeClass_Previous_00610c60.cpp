#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *PlanningNodeClass::Previous(TechnoClass *techno) (0x00610C60)
#include "shared/planning.hpp"

PlanningNodeClass *PlanningNodeClass::Previous(TechnoClass *techno)
{
    PlanningTokenClass *token = Planning_Token(techno);
    int index = token->Nodes.ID(this);
    if (index == -1) {
        return 0;
    }
    int count = token->Nodes.Count();
    if (count == 1) {
        return this;
    }
    if (--index < 0) {
        index = count - 1;
    }
    return token->Node_At(index);
}
