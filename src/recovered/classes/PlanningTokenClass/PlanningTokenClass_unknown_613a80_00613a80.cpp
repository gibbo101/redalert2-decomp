#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_613a80() (0x00613A80)
// Clears the loop marks of the loop start (once) and of every node from the
// first one on.
#include "shared/planning.hpp"

void PlanningTokenClass::unknown_613a80()
{
    if (unknown_98) {
        if (LoopStart != -1) {
            PlanningNodeClass *node = Nodes[LoopStart];
            if (node) {
                node->Clear_Loop_Marks();
            }
        }
        unknown_98 = false;
    }
    int start = unknown_8c != -1 ? unknown_8c : 0;
    int count = Nodes.Count();
    for (int i = start; i < count; i++) {
        PlanningNodeClass *node = Nodes[i];
        if (node) {
            node->Clear_Loop_Marks();
        }
    }
    unknown_8c = -1;
}
