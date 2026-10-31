// @ref ?color_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b634
// @ref ?pixel_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b638
#include "shared/win32_api.hpp"
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws a progress bar's fill of fraction (16.16) over area of surface: solid in the middle half of the rows,
// fading in from the left in the top and bottom quarters.
void __fastcall unknown_5fe7c0(Rect const &area, Surface *surface, int color, int fraction)
{
    int fade = 1;
    int run = (area.Width * fraction) >> 16;
    if (run < 0) return;
    if (run == 0) run = 1;
    unsigned short *pixels = (unsigned short *)surface->Lock();
    if (!pixels) return;
    for (int row = 0; row < area.Height; row++) {
        int index = area.X + (area.Y + row) * (surface->Stride() / 2);
        int quarter = area.Height / 4;
        if (row == quarter * 3) {
            fade = 1;
        }
        if (row == quarter) {
            fade = 0;
        }
        if (run > 0) {
            unsigned short *pixel = &pixels[index];
            for (int i = 0; i < run; i++) {
                if (fade) {
                    int alpha = (255 * (i + 1)) / area.Width;
                    *pixel = Blend_Color(*pixel, color, alpha);
                } else {
                    *pixel = color;
                }
                pixel++;
            }
        }
    }
    surface->Unlock();
}

}
