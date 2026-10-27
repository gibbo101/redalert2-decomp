#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Unlist_Node(PlanningNodeClass *node) (0x006143E0)
// Takes a node out of the three planning lists and forgets it if the
// planning mode was remembering it.
#include "shared/planning.hpp"

void __fastcall Planning_Unlist_Node(PlanningNodeClass *node)
{
    PlanningNodeClass::unknown_list_00a76758.Delete(node);
    PlanningNodeClass::unknown_list_00a76628.Delete(node);
    PlanningNodeClass::unknown_list_00a766d8.Delete(node);
    if (unknown_node_a7678c == node) {
        unknown_node_a7678c = 0;
    }
    if (unknown_node_a766f8 == node) {
        unknown_node_a766f8 = 0;
    }
    if (unknown_node_a766b0 == node) {
        unknown_node_a766b0 = 0;
    }
}
