#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *__stdcall Planning_Pick_Drawn(int x, int y) (0x00616140)
// The first drawn node (unknown_list_00a766d8) whose grown marker contains
// the screen point, or 0.
#include "shared/planning.hpp"

PlanningNodeClass *__stdcall Planning_Pick_Drawn(int x, int y)
{
    int count = PlanningNodeClass::unknown_list_00a766d8.Count();
    for (int i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a766d8[i];
        Point2D point(x, y);
        if (node->Hit_Rect().Is_Point_Within(point)) {
            return node;
        }
    }
    return 0;
}
