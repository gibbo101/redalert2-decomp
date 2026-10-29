#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Close_Loop(TechnoClass *techno, PlanningNodeClass *node) (0x006164E0)
// Makes the techno's path loop back to a node: the loop runs from the node's
// index to the path's end. The first time, the members of the path's last
// node owned by a human house get slot 81; then 0x00616A50 runs.
#include "shared/planning.hpp"
// @ref ?unknown_flag_a76788@@3_NA=00a76788
// @ref ?Planning_Unknown_616a50@@YIXPAVTechnoClass@@@Z=00616a50

// The index of a node in a token's path (expanded inline; name hypothesis).
static inline int Token_Node_Index(PlanningTokenClass *token, PlanningNodeClass *node)
{
    return token->Node_Index(node);
}

void __fastcall Planning_Close_Loop(TechnoClass *techno, PlanningNodeClass *node)
{
    int start = Token_Node_Index(Planning_Token(techno), node);
    PlanningTokenClass *token = Planning_Token(techno);
    int length = token->Nodes.Count() - start;
    token->LoopStart = start;
    token->unknown_98 = true;
    token->LoopLength = length;
    if (!unknown_flag_a76788) {
        if (techno->House->Unknown_004F52B0()) {
            unknown_flag_a76788 = true;
            PlanningNodeClass *last = token->Last_Node();
            int count = last->Members.Count();
            for (int i = 0; i < count; i++) {
                TechnoClass *member = last->Members[i]->Owner;
                if (member->unknown_77) {
                    member->unknown_slot81();
                }
            }
        }
        Planning_Unknown_616a50(techno);
    }
    node->unknown_611770();
}
