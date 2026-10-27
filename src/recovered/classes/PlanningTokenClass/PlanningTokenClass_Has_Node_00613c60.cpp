#define RA2_COORD_EQUAL_MEMBER
// bool PlanningTokenClass::Has_Node(PlanningNodeClass *node) (0x00613C60)
#include "shared/planning.hpp"

bool PlanningTokenClass::Has_Node(PlanningNodeClass *node)
{
    return Nodes.ID(node) != -1;
}
