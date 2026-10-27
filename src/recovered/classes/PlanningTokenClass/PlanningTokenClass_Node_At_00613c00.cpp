#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *PlanningTokenClass::Node_At(int index) const (0x00613C00)
// The node at index, wrapping into the loop past the end; 0 outside.
#include "shared/planning.hpp"

PlanningNodeClass *PlanningTokenClass::Node_At(int index) const
{
    int count = Nodes.Count();
    if (!count) {
        return 0;
    }
    if (index >= count) {
        if (LoopStart <= 0 && LoopStart != 0) {
            return 0;
        }
        index = (index - LoopStart) % LoopLength + LoopStart;
    }
    if (index < 0 || index >= count) {
        return 0;
    }
    return Nodes[index];
}
