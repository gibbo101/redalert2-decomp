#include "shared/palette_state.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_palette_00851cc8@@3VPaletteClass@@A=00851cc8
// @ref ?unknown_palette_00851fc8@@3PAUIDirectDrawPalette@@A=00851fc8
// @ref ?unknown_palette_entries_00851fcc@@3PAUPALETTEENTRY@@A=00851fcc
// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?unknown_palette_attached_008523d4@@3_NA=008523d4
// @ref ?unknown_palette_surface_008523d8@@3PAUIDirectDrawSurface@@A=008523d8
void PaletteClass::Set()
{
    if (this != &unknown_palette_00851cc8)
        memmove(&unknown_palette_00851cc8, this, sizeof(PaletteClass));
    IDirectDrawSurface *surface;
    if (DirectDrawObject && (surface = unknown_palette_surface_008523d8)) {
        unsigned char const *color = (unsigned char const *)Palette;
        for (int i = 0; i < 256; ++i) {
            int red = *color++;
            int green = *color++;
            int blue = *color++;
            unknown_palette_entries_00851fcc[i].peRed = (unsigned char)red;
            unknown_palette_entries_00851fcc[i].peGreen = (unsigned char)green;
            unknown_palette_entries_00851fcc[i].peBlue = (unsigned char)blue;
        }
        if (unknown_palette_00851fc8) {
            if (!unknown_palette_attached_008523d4) {
                surface->SetPalette(unknown_palette_00851fc8);
                unknown_palette_attached_008523d4 = true;
            }
            unknown_palette_00851fc8->SetEntries(0, 0, 256, unknown_palette_entries_00851fcc);
        }
    }
}
