// void unknown_init_color_ac1008() -- 0x006F1A40
// Sets the colour at 0x00AC1008 to (0x00, 0x52, 0x75).
#include "shared/rgb_class.hpp"
// @ref ?unknown_color_ac1008@@3VRGBClass@@A=00ac1008
extern RGBClass unknown_color_ac1008;

void __fastcall unknown_init_color_ac1008()
{
    unknown_color_ac1008.Red = 0x00;
    unknown_color_ac1008.Green = 0x52;
    unknown_color_ac1008.Blue = 0x75;
}
