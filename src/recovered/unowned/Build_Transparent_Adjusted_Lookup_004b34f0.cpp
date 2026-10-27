#include "shared/convert.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?Difference@RGBClass@@QBEHABV1@@Z=0063cfb0
// @ref ?Closest_Color@PaletteClass@@QBEHABVRGBClass@@@Z=006031b0
unsigned char *__fastcall Build_Transparent_Adjusted_Lookup_004b34f0(PaletteClass const &palette,
    unsigned char *lookup, int target_index, int ratio)
{
    RGBClass target = palette[target_index];
    lookup[0] = 0;
    for (int index = 1; index < 256; ++index) {
        RGBClass color = palette[index];
        color.Adjust(ratio, target);
        lookup[index] = (unsigned char)palette.Closest_Color(color);
    }
    return lookup;
}
