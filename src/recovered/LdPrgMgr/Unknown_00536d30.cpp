// void __fastcall Unknown_00536d30(surface, unknown, area, color, unknown_c) -- 0x00536D30
#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/hicolor.hpp"
#include "shared/text_print.hpp"
#include "shared/win32_api.hpp"
// @ref ?Unknown_005fe020@@YIXPAXPAVSurface@@PAURECT@@0HHHHHH@Z=005fe020

void __fastcall Unknown_00536d30(Surface *surface, void *unknown, Rect const &area, unsigned short color, int unknown_c)
{
    RECT rect;
    rect.left = area.X;
    rect.top = area.Y;
    rect.right = area.X + area.Width;
    rect.bottom = area.Y + area.Height;
    RGBClass rgb = Unpack_Hicolor_Pixel(color);
    Unknown_005fe020(unknown, surface, &rect, BitFont, rgb.Red | (rgb.Green << 8) | (rgb.Blue << 16), unknown_c, 12, 0, 0, 0);
}
