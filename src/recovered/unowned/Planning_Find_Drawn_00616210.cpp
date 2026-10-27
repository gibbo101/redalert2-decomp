#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *__stdcall Planning_Find_Drawn(CoordStruct coord) (0x00616210)
// The node on screen (unknown_list_00a766d8) at a coordinate, or 0.
#include "shared/planning.hpp"

PlanningNodeClass *__stdcall Planning_Find_Drawn(CoordStruct coord)
{
    int count = PlanningNodeClass::unknown_list_00a766d8.Count();
    for (int i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a766d8[i];
        CoordStruct here = node->Coord();
        if (here == coord) {
            return node;
        }
    }
    return 0;
}
