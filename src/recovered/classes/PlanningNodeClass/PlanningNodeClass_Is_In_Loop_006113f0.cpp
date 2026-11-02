#define RA2_COORD_EQUAL_MEMBER
// bool PlanningNodeClass::Is_In_Loop() (0x006113F0)
// True when this node lies in the closed loop of its first member's planning
// token: the token has a loop start and the node's index in the token's path
// is at or past it.
#include "shared/planning.hpp"

bool PlanningNodeClass::Is_In_Loop()
{
    if (!Members.Count()) {
        return false;
    }
    PlanningTokenClass *token = Planning_Token(Members[0]->Owner);
    int index = token->Nodes.ID(this);
    return token->LoopStart != -1 && index >= token->LoopStart;
}
