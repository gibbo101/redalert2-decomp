#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Highlight_Color() (0x0061A060)
// The colour the node's marker is drawn in: the plain one, or the lighter
// one when the node's first member is the one the planning mode is about to
// click (the remembered node's member, or an unmoved selected techno).
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849

int PlanningNodeClass::Highlight_Color()
{
    TechnoClass *owner = Members[0]->Owner;
    int result = Build_Hicolor_Pixel(unknown_rgb_ab6841.Red, unknown_rgb_ab6841.Green, unknown_rgb_ab6841.Blue);
    if (owner) {
        int lighter = Build_Hicolor_Pixel(unknown_rgb_ab6849.Red, unknown_rgb_ab6849.Green, unknown_rgb_ab6849.Blue);
        if (unknown_node_a766b0) {
            if (unknown_node_a766b0->Has_Member(owner)) {
                result = lighter;
            }
        } else if (owner->unknown_77) {
            result = lighter;
        }
    }
    return result;
}
