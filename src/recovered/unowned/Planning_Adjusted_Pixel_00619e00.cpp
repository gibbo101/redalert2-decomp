#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Adjusted_Pixel(RGBClass const &color, RGBClass const &target, int ratio) (0x00619E00)
// The screen pixel of a colour moved ratio/256 of the way toward target.
#include "shared/planning.hpp"
#include "shared/rgb_class.hpp"
#include "shared/hicolor.hpp"

#pragma auto_inline(off)
int __fastcall Planning_Adjusted_Pixel(RGBClass const &color, RGBClass const &target, int ratio)
{
    RGBClass adjusted = color;
    adjusted.Adjust(ratio, target);
    return Build_Hicolor_Pixel(adjusted.Red, adjusted.Green, adjusted.Blue);
}
#pragma auto_inline(on)
