#include "shared/palette_lookup.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_string.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?Closest_Color@PaletteClass@@QBEHABVRGBClass@@@Z=006031b0
// @ref ?Build_Remap_Adjusted_Lookup_004b3160=004b3160
unsigned char *__fastcall Build_Adjusted_Tables_004b3270(PaletteClass const &palette,
    PaletteLookupRule const *rules, int count, unsigned char *tables)
{
    if (count && rules) {
        if (!tables) tables = new unsigned char[(count + 1) * 256];
        if (tables) {
            memset(tables, 255, 256);
            unsigned char *output = tables + 256;
            for (int i = 0; i < count; ++i) {
                tables[rules[i].Key] = (unsigned char)i;
                int ratio = rules[i].Ratio;
                RGBClass target = palette[rules[i].ColorIndex];
                output[0] = 0;
                for (int index = 1; index < 256; ++index) {
                    RGBClass color = palette[index];
                    color.Adjust(ratio, target);
                    output[index] = (unsigned char)palette.Closest_Color(color);
                }
                output += 256;
            }
        }
    }
    return tables;
}
