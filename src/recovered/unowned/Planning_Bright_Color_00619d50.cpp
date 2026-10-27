#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Bright_Color(TechnoClass *techno) (0x00619D50)
// The screen colour of a techno's house, moved 100/256 toward the fade colour.
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20

int __fastcall Planning_Bright_Color(TechnoClass *techno)
{
    RGBClass color = Planning_House_Color(techno);
    color.Adjust(100, unknown_rgb_ab6849);
    return ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
}
