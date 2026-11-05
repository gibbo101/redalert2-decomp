#define RA2_COORD_EQUAL_MEMBER
#include "shared/planning.hpp"
#include "shared/hicolor_pixel.hpp"
// @ref ?RGB_To_Pixel@@YIHHHH@Z=00432d90
int __fastcall Planning_Pixel(RGBClass const *color)
{
    int red = color->Red;
    int green = color->Green;
    int blue = color->Blue;
    return RGB_To_Pixel(red, green, blue);
}
