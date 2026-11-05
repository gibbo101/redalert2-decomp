#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *__fastcall Planning_Find_Node(int house, int id, CoordStruct coord) (0x00615FB0)
// The node of unknown_list_00a76628 at a coordinate with the given id
// (-1: any) and house (-1: any).
#include "shared/planning.hpp"

PlanningNodeClass *__fastcall Planning_Find_Node(int house, int id, CoordStruct coord)
{
    int count = PlanningNodeClass::unknown_list_00a76628.Count();
    for (int i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a76628[i];
        if (node->Is_At(coord) && (id == -1 || id == node->unknown_18)) {
            int owner = Planning_House(node->Member_Owner(0));
            if (house == -1 || house == owner) {
                return node;
            }
        }
    }
    return 0;
}
