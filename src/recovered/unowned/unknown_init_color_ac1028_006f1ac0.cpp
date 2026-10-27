// void unknown_init_color_ac1028() -- 0x006F1AC0
// Sets the colour at 0x00AC1028 to black.
#include "shared/rgb_class.hpp"
// @ref ?unknown_color_ac1028@@3VRGBClass@@A=00ac1028
extern RGBClass unknown_color_ac1028;

void __fastcall unknown_init_color_ac1028()
{
    unknown_color_ac1028.Red = 0;
    unknown_color_ac1028.Green = 0;
    unknown_color_ac1028.Blue = 0;
}
