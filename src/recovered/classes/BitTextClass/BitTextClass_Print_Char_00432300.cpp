// int BitTextClass::Print_Char(BitFontClass *font, Surface *surface, wchar_t character, int x, int y) (0x00432300)
// Draws one character into the surface; returns the x after it.
#include "shared/text_print.hpp"
// @ref ?Set_Surface@BitFontClass@@QAEXPAVSurface@@@Z=004320b0
// @ref ?Set_unknown_20@BitFontClass@@QAEXH@Z=004318d0
// @ref ?Draw_Char@BitFontClass@@QAEHGHHH@Z=004318e0
// @ref ?Release_Surface@BitFontClass@@QAEXPAVSurface@@@Z=00432150

int BitTextClass::Print_Char(BitFontClass *font, Surface *surface, wchar_t character, int x, int y)
{
    int result = x;
    if (font) {
        font->Set_Surface(surface);
        font->Set_unknown_20(x);
        result = font->Draw_Char(character, x, y, -1);
        font->Release_Surface(surface);
    }
    return result;
}
