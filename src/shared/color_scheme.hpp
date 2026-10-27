// A colour scheme (ColorSchemes, 0x00AB6EF8): the name pointer, base colour, palette
// converter and the palette indices Draw_Box (0x004973D0) builds its box styles from.
// Schemes whose field +0x310 is 1 are not chosen by name. Names are hypotheses.
#ifndef RA2_SHARED_COLOR_SCHEME_HPP
#define RA2_SHARED_COLOR_SCHEME_HPP

#include "shared/hsv_class.hpp"
// Inline element access only (ColorSchemes[index]).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#include "shared/vector_class.hpp"

class ConvertClass;

class ColorScheme {
public:
    unsigned char unknown_000[0x304];
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
};
extern DynamicVectorClass<ColorScheme *> ColorSchemes;      // 0x00AB6EF8 (Vector at 0x00AB6EFC)

#endif
