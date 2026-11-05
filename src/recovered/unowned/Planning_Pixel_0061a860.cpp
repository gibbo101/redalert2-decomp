#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Pixel(RGBClass const *color) (0x0061A860)
// The screen pixel of a palette colour.
#include "shared/planning.hpp"
#include "shared/hicolor_pixel.hpp"
// @ref ?RGB_To_Pixel@@YIHHHH@Z=00432d90
int __fastcall Planning_Pixel(RGBClass const *color)
{
    RGBClass const &rgb = *color;
    int pixel = RGB_To_Pixel(rgb.Red, rgb.Green, rgb.Blue);
    return pixel;
}
