// void __fastcall Unknown_00536d30(text, surface, area, color, flags) -- 0x00536D30
#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/hicolor.hpp"
#include "shared/text_print.hpp"
#include "shared/win32_api.hpp"
// @ref ?unknown_draw_text_5fe020@OwnerDraw@@YIHPAVSurface@@PBGPAURECT@@PAVBitFontClass@@KHHHHH@Z=005fe020

void __fastcall Unknown_00536d30(wchar_t const *text, Surface *surface, Rect const &area, unsigned short color, int flags)
{
    RECT rect;
    rect.left = area.X;
    rect.top = area.Y;
    rect.right = area.X + area.Width;
    rect.bottom = area.Y + area.Height;
    RGBClass rgb = Unpack_Hicolor_Pixel(color);
    OwnerDraw::unknown_draw_text_5fe020(surface, text, &rect, BitFont, rgb.Red | (rgb.Green << 8) | (rgb.Blue << 16), flags, 12, 0, 0, 0);
}
