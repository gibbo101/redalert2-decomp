// Build_Light_Converter (0x00663690; Tiberian Sun scheme.cpp): copies the base palette into
// remapped, shades its sixteen-entry remap ramp (indices 16-31) from the colour and returns a
// light converter for it. Declared as Unknown_00663690 (shared/color_scheme.hpp): base is the
// base palette, unknown_b the screen palette, table the remap flags (hypotheses).
// @ref __real@8@3ffedf66f2ed08ad4800=007a9230
// @ref __real@8@3ffabea2f16e1be26000=007a9238
// @ref __real@8@3ffdb2b8c2573a243800=007a9240
// @ref __real@8@3ffba6ce934058661000=007a9248
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/light_convert.hpp"

ConvertClass *__fastcall Unknown_00663690(HSVClass const *hsv, void *base, int unknown_b, RGBClass *remapped,
    Surface *surface, int intensity_levels, int r, int g, int b, void const *table)
{
    int hue = hsv->Hue;
    int saturation = hsv->Saturation;
    int value = hsv->Value;

    *(PaletteClass *)remapped = *(PaletteClass const *)base;

    double cos_step = 0.08144869842640204;      // 14/3 degrees
    double sin_step = 0.046542113386515455;     // 8/3 degrees

    for (int i = 0; i < 16; i++) {
        double cosval = 0.3490658503988659 + (i * cos_step);    // 20 degrees
        double sinval = 0.8726646259971648 + (i * sin_step);    // 50 degrees
        if (i == 0) {
            cosval = 0.19634954084936207;                       // 11.25 degrees
        }

        int sat = int(unknown_sin_4ba480(sinval) * saturation);
        int val = int(unknown_cos_4ba4d0(cosval) * value);

        RGBClass rgb = HSVClass(hue, sat, val).To_RGB();
        (*(PaletteClass *)remapped)[i + 16] = rgb;
    }

    return new LightConvertClass(*(PaletteClass *)remapped, *(PaletteClass const *)unknown_b, surface, r, g, b,
        false, (unsigned char const *)table, intensity_levels);
}
