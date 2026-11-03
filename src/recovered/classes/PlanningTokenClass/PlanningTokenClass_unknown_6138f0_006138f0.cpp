#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_6138f0(int index) (0x006138F0)
// Takes the node at index out of the path: the first-node index (+0x8C) and
// the loop (LoopStart / LoopLength; a loop shorter than three nodes is
// dropped) are moved down, the owner leaves the node (Remove_Member, expanded
// inline; the node is destroyed when it has no members left) and the entry is
// deleted. Name hypothesis.
#include "shared/planning.hpp"

void PlanningTokenClass::unknown_6138f0(int index)
{
    if (Nodes.Count() == 1) {
        unknown_8c = -1;
    } else if (unknown_8c > 0 && index < unknown_8c) {
        unknown_8c--;
    }
    if (LoopStart >= 0) {
        if (index < LoopStart) {
            LoopStart--;
        } else if (--LoopLength < 3) {
            LoopStart = -1;
            LoopLength = 0;
        }
    }
    PlanningNodeClass *node = Nodes[index];
    node->Remove_Member(Owner);
    Nodes.Delete(index);
}
