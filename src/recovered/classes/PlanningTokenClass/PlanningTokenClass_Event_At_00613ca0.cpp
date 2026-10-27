#define RA2_COORD_EQUAL_MEMBER
// EventClass PlanningTokenClass::Event_At(int index) (0x00613CA0)
// The event of the token's techno in the node at index.
#include "shared/planning.hpp"

EventClass PlanningTokenClass::Event_At(int index)
{
    PlanningNodeClass *node = Nodes[index];
    return node->Event_For(Owner);
}
