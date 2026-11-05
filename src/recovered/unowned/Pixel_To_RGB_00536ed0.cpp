// Expand a screen-format pixel into RGB channels,00536ED0.
#include "shared/hicolor.hpp"
RGBClass __fastcall Pixel_To_RGB_00536ed0(unsigned short pixel)
{
    RGBClass color;
    color.Red = (pixel >> unknown_shift_852fb8) << unknown_shift_852fbc;
    color.Green = (pixel >> unknown_shift_852fc8) << unknown_shift_852fcc;
    color.Blue = (pixel >> unknown_shift_852fc0) << unknown_shift_852fc4;
    return color;
}
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
