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
class PaletteClass;
class Surface;

class ColorScheme {
public:
    ColorScheme();                          // 0x00663930 (unnamed, no converter; joins ColorSchemes)
    ColorScheme(char const *name, HSVClass const &base, void *unknown_a, int unknown_b, int unknown_c, bool add);   // 0x006639F0
    ~ColorScheme();                         // 0x00663BB0 (frees the name and converter, leaves ColorSchemes)
    // Rebuilds Converter from the palettes (0x00663B40; Tiberian Sun's Build_Light_Converters with scales).
    void Unknown_00663B40(PaletteClass *unknown_a, PaletteClass *palette, int rscale, int gscale, int bscale);

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
// The same ramp shaded into a copy of base, stored to remapped when given, with a plain converter
// (0x006637E0; Tiberian Sun's Build_Converter).
ConvertClass *__fastcall Build_Converter_006637e0(HSVClass const &hsv, PaletteClass const &base,
    PaletteClass const &screenpalette, Surface *surface, PaletteClass *remapped);
// Table sine and cosine (0x004BA480 / 0x004BA4D0) as the ramp builders call them: the products
// with the colour's saturation and value are doubles (shared/fast_math.hpp's Fast_Sin/Fast_Cos,
// declared returning float, are the same functions; bullet.hpp declares these too).
double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0
extern char const unknown_table_7f264c[];                  // 0x007F264C
extern DynamicVectorClass<ColorScheme *> ColorSchemes;      // 0x00AB6EF8 (Vector at 0x00AB6EFC)


// The lists of colour schemes kept per name at 0x00A76414 (made on first use;
// RulesClass::Colors registers its colours there through 0x00603A60). An
// iterator over the lists (0x00603640 returns the next one, null at the end)
// and the count 0x00603C10 returns (the +0x10 of the table's +4 list).
// Hypotheses: names and the element type.
struct UnknownSchemeListIterator {
    UnknownSchemeListIterator() : Bucket(0), Index(0), Done(false) {}
    DynamicVectorClass<ColorScheme *> *Next();   // 0x00603640
    int Bucket;     // +0x0
    int Index;      // +0x4
    bool Done;      // +0x8
};
int Unknown_00603C10();                         // 0x00603C10

#endif
