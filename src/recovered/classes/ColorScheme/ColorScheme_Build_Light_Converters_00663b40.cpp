// ColorScheme::Unknown_00663B40 (0x00663B40; Tiberian Sun's Build_Light_Converters): throws away
// the converter and rebuilds it from the palettes with the tint.
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
// @ref ?Unknown_00663690@@YIPAVConvertClass@@PBVHSVClass@@PAXHPAVRGBClass@@PAVSurface@@HHHHPBX@Z=00663690
// @ref ?unknown_table_7f264c@@3QBDB=007f264c
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
#include "shared/unknown_globals.hpp"

void ColorScheme::Unknown_00663B40(PaletteClass *unknown_a, PaletteClass *palette, int rscale, int gscale, int bscale)
{
    if (Converter != 0) {
        delete Converter;
        Converter = 0;
    }

    Converter = Unknown_00663690(&BaseColor, unknown_a, (int)palette, Palette, unknown_surface_839950, unknown_0x310,
        rscale, gscale, bscale, unknown_table_7f264c);
}
