// int BitTextClass::Print_Bold(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int count) (0x004323B0)
// Draws the string; with the font's unknown_40 set it is drawn twice, one
// pixel apart, with one more pixel between characters.
#include "shared/text_print.hpp"
// @ref ?Set_Surface@BitFontClass@@QAEXPAVSurface@@@Z=004320b0
// @ref ?Set_unknown_20@BitFontClass@@QAEXH@Z=004318d0
// @ref ?Draw_String@BitFontClass@@QAEHPBGHHHH@Z=00431cc0
// @ref ?Release_Surface@BitFontClass@@QAEXPAVSurface@@@Z=00432150

int BitTextClass::Print_Bold(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int count)
{
    int result = 0;
    if (font) {
        if (font->unknown_40) {
            font->unknown_2c = 2;
            font->Set_Surface(surface);
            font->Set_unknown_20(x);
            font->Draw_String(text, x, y, count, 0);
            font->Release_Surface(surface);
            int next = x + 1;
            font->Set_Surface(surface);
            font->Set_unknown_20(next);
            result = font->Draw_String(text, next, y, count, 0);
            font->Release_Surface(surface);
            font->unknown_2c = 1;
        } else {
            font->Set_Surface(surface);
            font->Set_unknown_20(x);
            result = font->Draw_String(text, x, y, count, 0);
            font->Release_Surface(surface);
        }
    }
    return result;
}
