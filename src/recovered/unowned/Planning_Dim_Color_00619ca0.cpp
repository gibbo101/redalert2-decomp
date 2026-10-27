#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Dim_Color(TechnoClass *techno) (0x00619CA0)
// The screen colour of a techno's house, moved 0x50/256 toward the fade colour.
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20

int __fastcall Planning_Dim_Color(TechnoClass *techno)
{
    RGBClass color = Planning_House_Color(techno);
    color.Adjust(0x50, unknown_rgb_ab6841);
    return ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
}
