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
    int plain = Planning_Pixel(&unknown_rgb_ab6841);
    if (!techno) return plain;
    int lighter = Planning_Pixel(&unknown_rgb_ab6849);
    if (unknown_node_a766b0) {
        if (unknown_node_a766b0->Member_Index(techno) != -1) return lighter;
        return plain;
    }
    if (techno->unknown_77) return lighter;
    return plain;
}
