#include "shared/palette_lookup.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_string.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?Closest_Color@PaletteClass@@QBEHABVRGBClass@@@Z=006031b0
// @ref ?Build_Remap_Adjusted_Lookup_004b3160=004b3160
unsigned char *__fastcall Build_Remap_Adjusted_Tables_004b33b0(PaletteClass const &palette,
    PaletteLookupRule const *rules, int count, unsigned char *tables)
{
    if (count && rules && (tables || (tables = new unsigned char[(count + 1) * 256]))) {
        int i = 0;
        memset(tables, 255, 256);
        unsigned char *output = tables + 256;
        for (; i < count; ++i) {
            tables[rules[i].Key] = (unsigned char)i;
            Build_Remap_Adjusted_Lookup_004b3160(palette, output,
                rules[i].ColorIndex, rules[i].Ratio);
            output += 256;
        }
    }
    return tables;
}
