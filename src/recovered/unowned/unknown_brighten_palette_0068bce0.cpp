#include "shared/rgb_class.hpp"
#include "shared/pcx_cache.hpp"
// Palette transform at0068BCE0; native reads green, blue, then red, and preserves int signed division.
void __fastcall unknown_brighten_palette_68bce0(unsigned char *palette)
{
    RGBClass *colors = (RGBClass *)palette;
    for (int i = 0; i < 256; ++i) {
        int green = colors[i].Green;
        int red = colors[i].Red;
        int blue = colors[i].Blue;
        colors[i].Red = (unsigned char)(green * 15 / 10 > 255 ? 255 : green * 15 / 10);
        colors[i].Green = (unsigned char)red;
        colors[i].Blue = (unsigned char)(blue / 4);
    }
}
