#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *__stdcall Planning_Node_At(int x, int y) (0x00615D30)
// The remembered node (0x00A7678C) when its grown marker contains the screen point, or 0.
#include "shared/planning.hpp"
// @ref ?unknown_node_a7678c@@3PAVPlanningNodeClass@@A=00a7678c

PlanningNodeClass *__stdcall Planning_Node_At(int x, int y)
{
    if (!unknown_node_a7678c) {
        return 0;
    }
    Point2D point(x, y);
    if (unknown_node_a7678c->Hit_Rect().Is_Point_Within(point)) {
        return unknown_node_a7678c;
    }
    return 0;
}
