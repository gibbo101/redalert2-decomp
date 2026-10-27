// Palette adjustment lookup builders in the 004B3160 unit.
#ifndef RA2_SHARED_PALETTE_LOOKUP_HPP
#define RA2_SHARED_PALETTE_LOOKUP_HPP
#include "shared/convert.hpp"
struct PaletteLookupRule {
    unsigned char Key;
    unsigned char ColorIndex;
    unsigned char Ratio;
    unsigned char unknown_03;
};
unsigned char *__fastcall Build_Remap_Adjusted_Lookup_004b3160(PaletteClass const &palette,
    unsigned char *lookup, int target_index, int ratio);
#endif
