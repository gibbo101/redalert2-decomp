// bool BitTextClass::Print_Box_Shadow(...) (0x00432B00): Print_Box in the font's unknown_26 colour one pixel
// down and right, then in its own colour. Names are hypotheses.
#include "shared/text_print.hpp"
// @ref ?Set_unknown_20@BitFontClass@@QAEXH@Z=004318d0
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ?Print_Box@BitTextClass@@QAE_NPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490

bool BitTextClass::Print_Box_Shadow(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y,
                                    int width, int height, int arg8, int arg9, int arg10)
{
    if (font == 0) {
        return false;
    }
    font->Set_unknown_20(x);
    unsigned short shadow = font->unknown_26;
    unsigned short color = font->Set_Color(shadow);
    Print_Box(font, surface, text, x + 1, y + 1, width, height, arg8, arg9, arg10);
    font->Set_Color(color);
    return Print_Box(font, surface, text, x, y, width, height, arg8, arg9, arg10);
}
