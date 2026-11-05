#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Fill_Marker_Colored() (0x00619BD0)
// Fills the node marker in the node's own colour.
// void __fastcall Planning_Fill_Node(PlanningNodeClass *node) (0x00619BD0; no direct callers, name a hypothesis)
// Fills the node's marker in its own colour.
#include "shared/planning.hpp"

void __fastcall Planning_Fill_Node(PlanningNodeClass *node)
{
    node->Fill_Marker(node->Color());
}
