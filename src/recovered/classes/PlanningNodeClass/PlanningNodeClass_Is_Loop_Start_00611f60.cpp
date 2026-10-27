#define RA2_COORD_EQUAL_MEMBER
// bool PlanningNodeClass::Is_Loop_Start(TechnoClass *techno) (0x00611F60)
// Whether this node is where the techno's path loops back to.
#include "shared/planning.hpp"

bool PlanningNodeClass::Is_Loop_Start(TechnoClass *techno)
{
    PlanningTokenClass *token = Planning_Token(techno);
    return token->Nodes.ID(this) == token->LoopStart;
}
