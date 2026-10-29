// void __fastcall Unknown_00536c70(text, surface, x, y, width, flags, fill) -- 0x00536C70
#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/text_print.hpp"
// @ref ?Unknown_005feb60@@YIXPAVRect@@PAVSurface@@HH@Z=005feb60

void __fastcall Unknown_00536c70(wchar_t const *text, Surface *surface, int x, int y, int width, int flags, bool fill)
{
    int text_width = 0;
    int text_height = 0;
    BitFont->Get_Text_Area(text, &text_width, &text_height, width);
    if (fill) {
        text_width = width;
    }
    Rect area;
    area = Rect(x, y, text_width, text_height);
    if (flags & 1) {
        area.X = (width - text_width) / 2 + x;
    } else if (flags & 2) {
        area.X = x - text_width + width;
    }
    Unknown_Rect_Shrink_006F1B00(&area, -4);
    Unknown_005feb60(&area, surface, 0, 0x9F);
}
