#include "shared/convert.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?Difference@RGBClass@@QBEHABV1@@Z=0063cfb0
// @ref ?Closest_Color@PaletteClass@@QBEHABVRGBClass@@@Z=006031b0
unsigned char *__fastcall Build_Remap_Adjusted_Lookup_004b3160(PaletteClass const &palette,
    unsigned char *lookup, int target_index, int ratio)
{
    if (lookup) {
        unsigned char *output = lookup;
        for (int index = 0; index < 256; ++index) {
            if (index <= 240 && index != 0) {
                RGBClass color = palette[index];
                color.Adjust(ratio, palette[target_index]);
                int best = -1;
                int distance = 0;
                for (int candidate = 240; candidate < 255; ++candidate) {
                    int current = palette[candidate].Difference(color);
                    if (best == -1 || current < distance) {
                        best = candidate;
                        distance = current;
                    }
                }
                *output++ = (unsigned char)best;
            } else {
                *output++ = (unsigned char)index;
            }
        }
    }
    return lookup;
}
