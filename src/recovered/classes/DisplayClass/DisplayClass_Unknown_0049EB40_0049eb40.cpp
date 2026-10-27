// void DisplayClass::Unknown_0049EB40(int color) (0x0049EB40)
// Loads eight colours of the palette at 0x00837810 (block color % 12, or
// the first block for -1) into entries 1-8 of the drawer 0x008323C8's
// surface value table, as screen pixels.
#include "shared/display.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_drawer_8323c8@@3PAVConvertClass@@A=008323c8
// @ref ?unknown_palette_837810@@3VPaletteClass@@A=00837810
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc

extern ConvertClass *unknown_drawer_8323c8;     // 0x008323C8
extern PaletteClass unknown_palette_837810;     // 0x00837810

void DisplayClass::Unknown_0049EB40(int color)
{
    int base = color == -1 ? 0 : color % 12 * 8;
    unsigned short *table = (unsigned short *)unknown_drawer_8323c8->Table;
    for (int index = 0; index < 8; index++) {
        RGBClass rgb = unknown_palette_837810[index + base];
        table[index + 1] = (unsigned short)Build_Hicolor_Pixel(rgb.Red, rgb.Green, rgb.Blue);
    }
}
