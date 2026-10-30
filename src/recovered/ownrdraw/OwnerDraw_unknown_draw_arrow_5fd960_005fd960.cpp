// @ref ??_C@_0P@BHGD@guparrow?$CFc?4pcx?$AA@=007eb560
// @ref ??_C@_0P@INFD@gdnarrow?$CFc?4pcx?$AA@=007eb550
// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
#include "shared/surface.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws the up or down scroll arrow image (released or pressed; "g"-prefixed art when prefixed) at its own
// size from the top left corner of rect.
void __fastcall unknown_draw_arrow_5fd960(Surface *surface, Rect const &rect, int upward, int pressed, bool prefixed)
{
    char name[32];
    char state = 'r';
    if (pressed) {
        state = 'p';
    }
    if (upward) {
        sprintf(name, "guparrow%c.pcx", state);
    } else {
        sprintf(name, "gdnarrow%c.pcx", state);
    }
    Surface *arrow = unknown_bitmap_writer_a76378.Get_Image_0068ca40(name + !prefixed, 0);
    Rect destination = rect;
    destination.Width = arrow->Get_Width();
    destination.Height = arrow->Get_Height();
    Rect source;
    source.Y = 0;
    source.X = 0;
    source.Width = arrow->Get_Width();
    source.Height = arrow->Get_Height();
    surface->Copy_From(destination, *arrow, source, false, true);
}

}
