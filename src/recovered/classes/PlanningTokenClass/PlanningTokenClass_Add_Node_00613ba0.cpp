#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::Add_Node(PlanningNodeClass *node) (0x00613BA0)
// Appends a node to the path; the first one added is where the path starts.
#include "shared/planning.hpp"

void PlanningTokenClass::Add_Node(PlanningNodeClass *node)
{
    Nodes.Add(node);
    if (unknown_8c == -1) {
        unknown_8c = Nodes.Count() - 1;
    }
}
