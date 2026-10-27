#include "shared/convert.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?Difference@RGBClass@@QBEHABV1@@Z=0063cfb0
// @ref ?Closest_Color@PaletteClass@@QBEHABVRGBClass@@@Z=006031b0
unsigned char *__fastcall Build_Adjusted_Lookup_004b3460(PaletteClass const &palette,
    unsigned char *lookup, int target_index, int ratio)
{
    if (lookup) {
        int index = 0;
        for (; index < 256; ++index) {
            RGBClass color = palette[index];
            color.Adjust(ratio, palette[target_index]);
            lookup[index] = (unsigned char)palette.Closest_Color(color);
        }
    }
    return lookup;
}
