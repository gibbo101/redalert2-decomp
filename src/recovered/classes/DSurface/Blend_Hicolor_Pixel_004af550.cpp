// unsigned short Blend_Hicolor_Pixel(unsigned short color, unsigned short background, int percent) (0x004AF550)
// Mixes two screen pixels for percent 0, 25, 50, 75 or 100 (any other value
// keeps color): 0 gives background, 50 the average of the two through the
// half-brightness mask. As compiled, 25 and 75 both give color itself
// masked to multiples of four per channel (the background is not read);
// the original expressions for those two cases are not known. The name is
// a hypothesis.
#include "shared/hicolor.hpp"
// @ref ?unknown_half_mask_852fd0@@3GA=00852fd0
// @ref ?unknown_quarter_mask_852fd2@@3GA=00852fd2

// The half mask is defined in this unit: the compiler then zero-extends it
// with a 32-bit load (the quarter mask, read as a word, is only declared).
unsigned short unknown_half_mask_852fd0;

unsigned short __fastcall Blend_Hicolor_Pixel(unsigned short color, unsigned short background, int percent)
{
    switch (percent) {
    case 75:
        return (unsigned short)(((color >> 2) & unknown_quarter_mask_852fd2) * 4);
    case 50:
        return (unsigned short)(((color >> 1) & unknown_half_mask_852fd0) + ((background >> 1) & unknown_half_mask_852fd0));
    case 25:
        return (unsigned short)(((color >> 2) & unknown_quarter_mask_852fd2) * 4);
    case 0:
        return background;
    case 100:
        return color;
    }
    return color;
}
