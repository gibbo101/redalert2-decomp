// int BitTextClass::Print(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int arg6, int arg7) (0x00432350)
// Draws a string into the surface; returns what Draw_String does (x without a font).
#include "shared/text_print.hpp"
// @ref ?Set_Surface@BitFontClass@@QAEXPAVSurface@@@Z=004320b0
// @ref ?Set_unknown_20@BitFontClass@@QAEXH@Z=004318d0
// @ref ?Draw_String@BitFontClass@@QAEHPBGHHHH@Z=00431cc0
// @ref ?Release_Surface@BitFontClass@@QAEXPAVSurface@@@Z=00432150

int BitTextClass::Print(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int arg6, int arg7)
{
    int result = x;
    if (font) {
        font->Set_Surface(surface);
        font->Set_unknown_20(x);
        result = font->Draw_String(text, x, y, arg6, arg7);
        font->Release_Surface(surface);
    }
    return result;
}
