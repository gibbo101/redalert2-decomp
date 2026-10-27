#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Techno_Color(TechnoClass *techno) (0x00619E80)
// The colour a techno's marker is drawn in: the plain one, or the lighter
// one for the remembered node's members (or an unmoved selected techno).
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849

int __fastcall Planning_Techno_Color(TechnoClass *techno)
{
    int result = Build_Hicolor_Pixel(unknown_rgb_ab6841.Red, unknown_rgb_ab6841.Green, unknown_rgb_ab6841.Blue);
    if (techno) {
        int lighter = Build_Hicolor_Pixel(unknown_rgb_ab6849.Red, unknown_rgb_ab6849.Green, unknown_rgb_ab6849.Blue);
        if (unknown_node_a766b0) {
            if (unknown_node_a766b0->Has_Member(techno)) {
                result = lighter;
            }
        } else if (techno->unknown_77) {
            result = lighter;
        }
    }
    return result;
}
