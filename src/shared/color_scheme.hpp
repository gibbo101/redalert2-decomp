// A colour scheme (ColorSchemes, 0x00AB6EF8): the name pointer, base colour, palette
// converter and the palette indices Draw_Box (0x004973D0) builds its box styles from.
// Schemes whose field +0x310 is 1 are not chosen by name. Names are hypotheses.
#ifndef RA2_SHARED_COLOR_SCHEME_HPP
#define RA2_SHARED_COLOR_SCHEME_HPP

#include "shared/hsv_class.hpp"
#include "shared/rgb_class.hpp"
// Inline element access only (ColorSchemes[index]).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#include "shared/vector_class.hpp"

class ConvertClass;
class Surface;

class ColorScheme {
public:
    ColorScheme(char const *name, HSVClass const &base, void *unknown_a, int unknown_b, int unknown_c, bool add);   // 0x006639F0
    ~ColorScheme();                         // 0x00663BB0 (frees the name and converter, leaves ColorSchemes)

    int Index;                              // +0x000 ColorSchemes.Count() after the scheme was added
    RGBClass Palette[256];                  // +0x004 the scheme's palette

    char const *Name;                       // +0x304
    HSVClass BaseColor;                     // +0x308 (name hypothesis)
    ConvertClass *Converter;                // +0x30C converts the palette indices below
    int unknown_0x310;                      // +0x310 (1: not chosen by name)
    int unknown_0x314;
    int unknown_0x318;
    int unknown_color_0x31c;                // +0x31C
    int unknown_color_0x320;                // +0x320
    int unknown_color_0x324;                // +0x324
    int unknown_color_0x328;                // +0x328
    int unknown_color_0x32c;                // +0x32C
    int unknown_color_0x330;                // +0x330 (the palette index of a house's colour; HouseClass::Read_INI)
    int unknown_0x334;
    int unknown_0x338;
};
// Builds the converter for a base colour into a 256-entry palette (0x00663690; hypothesis).
ConvertClass *__fastcall Unknown_00663690(HSVClass const *base, void *unknown_a, int unknown_b, RGBClass *palette,
    Surface *surface, int unknown_c, int rscale, int gscale, int bscale, void const *table);
extern char const unknown_table_7f264c[];                  // 0x007F264C
extern DynamicVectorClass<ColorScheme *> ColorSchemes;      // 0x00AB6EF8 (Vector at 0x00AB6EFC)

#endif
