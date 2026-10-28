// ColorScheme::ColorScheme(...) -- 0x006639F0
// Builds a colour scheme from a base colour and, when asked, adds it to ColorSchemes.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/color_scheme.hpp"
#include "shared/unknown_globals.hpp"
// @ref _strdup=0078d816
// @ref ?Unknown_00663690@@YIPAVConvertClass@@PBVHSVClass@@PAXHPAVRGBClass@@PAVSurface@@HHHHPBX@Z=00663690
// @ref ?unknown_table_7f264c@@3QBDB=007f264c
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
extern "C" char *__cdecl strdup(char const *string);

ColorScheme::ColorScheme(char const *name, HSVClass const &base, void *unknown_a, int unknown_b, int unknown_c, bool add) :
    Name(strdup(name)),
    BaseColor(base)
{
    Converter = 0;
    unknown_0x310 = unknown_c;
    unknown_0x314 = 0x10;
    unknown_0x318 = 0xF;
    unknown_color_0x31c = 0x19;
    unknown_color_0x320 = 0x18;
    unknown_color_0x324 = 0x16;
    unknown_color_0x328 = 0x10;
    unknown_color_0x32c = 0x13;
    unknown_color_0x330 = 0x10;
    unknown_0x334 = 0x10;
    unknown_0x338 = 0x15;
    Converter = Unknown_00663690(&BaseColor, unknown_a, unknown_b, Palette, unknown_surface_839950, unknown_c, 1000, 1000, 1000, unknown_table_7f264c);
    if (add) {
        ColorSchemes.Add(this);
        Index = ColorSchemes.Count();
    }
}
