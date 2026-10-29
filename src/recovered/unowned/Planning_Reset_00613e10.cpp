#define RA2_COORD_EQUAL_MEMBER
// void Planning_Reset() (0x00613E10)
// Clears the planning mode's flags and remembered nodes.
#include "shared/planning.hpp"
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4
// @ref ?unknown_flag_a767a5@@3_NA=00a767a5
// @ref ?unknown_node_a7678c@@3PAVPlanningNodeClass@@A=00a7678c
// @ref ?unknown_node_a766f8@@3PAVPlanningNodeClass@@A=00a766f8
// @ref ?unknown_node_a766b0@@3PAVPlanningNodeClass@@A=00a766b0
// @ref ?unknown_point_a76728@@3UPoint2D@@A=00a76728
// @ref ?unknown_flag_a76770@@3_NA=00a76770

void Planning_Reset()
{
    unknown_flag_a767a4 = false;
    unknown_flag_a767a5 = false;
    unknown_node_a7678c = 0;
    unknown_node_a766f8 = 0;
    unknown_node_a766b0 = 0;
    unknown_point_a76728 = Point2D(0, 0);
    unknown_flag_a76770 = false;
}
