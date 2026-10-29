#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Selection_Node_State(PlanningNodeClass *node) (0x00617A10)
// Where a node stands in the paths of the selected technos: 1 when a path
// is closed into a loop, 5 when a path lacks the node, 2 / 3 when it is the
// last / next to last node of a path, else -1. Name hypothesis.
#include "shared/planning.hpp"

int __fastcall Planning_Selection_Node_State(PlanningNodeClass *node)
{
    int count = unknown_objects_a40c60.Count();
    for (int i = 0; i < count; i++) {
        ObjectClass *object = unknown_objects_a40c60[i];
        bool techno;
        if (object != 0) {
            techno = object->unknown_14_bit0;
        }
        if (object != 0 && techno) {
            PlanningTokenClass *token = Planning_Token((TechnoClass *)object);
            if (token != 0) {
                bool looped = token->LoopStart > 0 || token->LoopStart == 0;
                if (looped) {
                    return 1;
                }
                int index = token->Node_Index(node);
                if (index == -1) {
                    return 5;
                }
                if (index == token->Nodes.Count() - 1) {
                    return 2;
                }
                if (index == token->Nodes.Count() - 2) {
                    return 3;
                }
            }
        }
    }
    return -1;
}
