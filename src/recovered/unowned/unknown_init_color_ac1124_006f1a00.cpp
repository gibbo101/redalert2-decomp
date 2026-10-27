// void unknown_init_color_ac1124() -- 0x006F1A00
// Sets the colour at 0x00AC1124 to (0xFF, 0xFF, 0).
#include "shared/rgb_class.hpp"
// @ref ?unknown_color_ac1124@@3VRGBClass@@A=00ac1124
extern RGBClass unknown_color_ac1124;

void __fastcall unknown_init_color_ac1124()
{
    unknown_color_ac1124.Red = 0xff;
    unknown_color_ac1124.Green = 0xff;
    unknown_color_ac1124.Blue = 0;
}
