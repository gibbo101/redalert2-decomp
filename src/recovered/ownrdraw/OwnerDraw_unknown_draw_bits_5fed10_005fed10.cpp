// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
// @ref ?Draw_0068cf90@UnknownBitmapWriter@@QAE_NABVRect@@PAVSurface@@11PAEHHH@Z=0068cf90
// @ref ?unknown_brighten_palette_68bce0@@YIXPAE@Z=0068bce0
// @ref ??_C@_0L@HADO@bits_a?4pcx?$AA@=007eb570
// @ref ??_C@_0L@HBBE@bits_i?4pcx?$AA@=007eb57c
// @ref _rand=007846aa
#include "shared/crt_memory.hpp"
#include "shared/rect.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws a row of random bits_i.pcx frames (10x12, through bits_a.pcx, brightened palette) along the top
// and bottom edges of area, with a 10-pixel gap after every sixth (0x005FED10).
void __fastcall unknown_draw_bits_5fed10(Rect const *area, Surface *surface)
{
    unsigned char palette[768];
    Surface *image = unknown_bitmap_writer_a76378.Get_Image_0068ca40("bits_i.pcx", (int)palette);
    Surface *alpha = unknown_bitmap_writer_a76378.Get_Image_0068ca40("bits_a.pcx", 0);
    int count = 0;
    unknown_brighten_palette_68bce0(palette);
    int x = 0;
    Rect rect = *area;
    if (x < area->Width) {
        do {
            int frame = rand() % 8;
            rect.X = area->X + x;
            rect.Y = area->Y + 1;
            rect.Width = 10;
            rect.Height = 12;
            unknown_bitmap_writer_a76378.Draw_0068cf90(rect, surface, image, alpha, palette, 0, frame * 10, 0);
            frame = rand() % 8;
            rect.X = area->X + x;
            rect.Width = 10;
            rect.Height = 12;
            rect.Y = area->Y + area->Height - 16;
            unknown_bitmap_writer_a76378.Draw_0068cf90(rect, surface, image, alpha, palette, 0, frame * 10, 0);
            count++;
            if (count % 6 == 0) {
                x += 10;
            }
            x += 10;
        } while (x < area->Width);
    }
}

}
