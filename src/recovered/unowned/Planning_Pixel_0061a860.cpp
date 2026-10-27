#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Pixel(RGBClass const *color) (0x0061A860)
// The screen pixel of a palette colour.
#include "shared/planning.hpp"
#include "shared/hicolor.hpp"

int __fastcall Planning_Pixel(RGBClass const *color)
{
    return ((color->Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((color->Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((color->Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
}
