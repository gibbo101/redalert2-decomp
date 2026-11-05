// The out-of-line RGB screen-pixel packing body after BitText.cpp, 00432D90.
#include "shared/hicolor.hpp"
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
int __fastcall RGB_To_Pixel_00432d90(int red, int green, int blue)
{
    return ((red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
}
