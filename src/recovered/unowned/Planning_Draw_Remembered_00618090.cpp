#define RA2_COORD_EQUAL_MEMBER
// void Planning_Draw_Remembered() (0x00618090; called from Tactical 0x6A503A, not yet recovered)
// Outlines the remembered nodes 0x00A7678C and 0x00A766B0 in the fade colour.
#include "shared/planning.hpp"

void Planning_Draw_Remembered()
{
    int color = Planning_Pixel(&unknown_rgb_ab6849);
    if (unknown_node_a7678c) {
        unknown_node_a7678c->Draw_Outer_Outline(color);
    }
    if (unknown_node_a766b0) {
        unknown_node_a766b0->Draw_Marker_Outline(color);
    }
}
