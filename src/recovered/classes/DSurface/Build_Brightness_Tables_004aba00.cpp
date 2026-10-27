// void Build_Brightness_Tables(unsigned short *table, int count, PaletteClass const &palette) (0x004ABA00)
// Builds count 256-entry screen pixel tables of palette, table n scaled by
// 2n / (count - 1) in 16.16 fixed point (a single table is unscaled), each
// channel saturating at 255. The name is a hypothesis.
#include "shared/hicolor.hpp"
#include "shared/palette.hpp"
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc

void __fastcall Build_Brightness_Tables(unsigned short *table, int count, PaletteClass const &palette)
{
    if (count < 1) {
        return;
    }
    for (int shade = 0; shade <= count - 1; shade++) {
        int scale;
        if (count > 1) {
            scale = (shade * 0x20000) / (count - 1);
        } else {
            scale = 0x10000;
        }
        for (int index = 0; index < 256; index++) {
            RGBClass const &color = palette[index];
            int red = (color.Red * scale) >> 16;
            int green = (color.Green * scale) >> 16;
            int blue = (color.Blue * scale) >> 16;
            if (red >= 255) {
                red = 255;
            }
            if (green >= 255) {
                green = 255;
            }
            if (blue >= 255) {
                blue = 255;
            }
            *table++ = (unsigned short)Build_Hicolor_Pixel(red, green, blue);
        }
    }
}
