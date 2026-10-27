#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Queue_Node(PlanningNodeClass *node) (0x00614650)
// Marks a node as queued and appends it once to unknown_list_00a76758.
#include "shared/planning.hpp"

void __fastcall Planning_Queue_Node(PlanningNodeClass *node)
{
    if (node != 0 && !node->IsQueued) {
        node->IsQueued = true;
        PlanningNodeClass::unknown_list_00a76758.Add(node);
    }
}
