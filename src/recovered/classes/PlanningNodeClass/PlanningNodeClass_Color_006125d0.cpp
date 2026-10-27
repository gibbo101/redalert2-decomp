#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Color() (0x006125D0)
// The node's screen colour (cached in unknown_b4): its first member's house
// colour, moved toward white; a node whose pixel is taken by one of its
// branches, or that starts a loop, is drawn a shade closer to white.
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849

int PlanningNodeClass::Color()
{
    if (unknown_b4 != -1) {
        return unknown_b4;
    }
    TechnoClass *owner = Members[0]->Owner;
    unknown_b4 = Planning_Adjusted_Pixel(Planning_House_Color(owner), unknown_rgb_ab6841, 0x50);
    int branches = Branches.Count();
    for (int i = 0; i < branches; i++) {
        if (Branches[i]->unknown_74 == unknown_b4) {
            return unknown_b4;
        }
    }
    if (branches == 0) {
        PlanningTokenClass *token = Planning_Token(owner);
        if (token->Reached(token->Nodes.ID(this))) {
            RGBClass loop_color = Planning_House_Color(owner);
            loop_color.Adjust(100, unknown_rgb_ab6849);
            unknown_b4 = Build_Hicolor_Pixel(loop_color.Red, loop_color.Green, loop_color.Blue);
        }
    } else {
        RGBClass branch_color = Planning_House_Color(owner);
        branch_color.Adjust(100, unknown_rgb_ab6849);
        unknown_b4 = Build_Hicolor_Pixel(branch_color.Red, branch_color.Green, branch_color.Blue);
    }
    return unknown_b4;
}
