// Build_Converter (0x006637E0; Tiberian Sun scheme.cpp): shades the sixteen-entry remap ramp
// from the colour into a copy of the base palette and returns a plain converter for it.
// @ref __real@8@3ffedf66f2ed08ad4800=007a9230
// @ref __real@8@3ffabea2f16e1be26000=007a9238
// @ref __real@8@3ffdb2b8c2573a243800=007a9240
// @ref __real@8@3ffba6ce934058661000=007a9248
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"

ConvertClass *__fastcall Build_Converter_006637e0(HSVClass const &hsv, PaletteClass const &base,
    PaletteClass const &screenpalette, Surface *surface, PaletteClass *remapped)
{
    int hue = hsv.Hue;
    int saturation = hsv.Saturation;
    int value = hsv.Value;

    PaletteClass pal = base;

    double cos_step = 0.08144869842640204;      // 14/3 degrees
    double sin_step = 0.046542113386515455;     // 8/3 degrees

    for (int i = 0; i < 16; i++) {
        double cosval = 0.3490658503988659 + (i * cos_step);
        double sinval = 0.8726646259971648 + (i * sin_step);
        if (i == 0) {
            cosval = 0.19634954084936207;
        }

        int sat = int(unknown_sin_4ba480(sinval) * saturation);
        int val = int(unknown_cos_4ba4d0(cosval) * value);

        RGBClass rgb = HSVClass(hue, sat, val).To_RGB();
        pal[i + 16] = rgb;
    }

    if (remapped != 0) {
        *remapped = pal;
    }

    return new ConvertClass(pal, screenpalette, surface, 1, false);
}
