// bool BitTextClass::Print_Box_Bold(...) (0x00432BB0): Print_Box; with the font's unknown_40 set it is drawn
// twice, one pixel apart, with one more pixel between characters (as Print_Bold). Names are hypotheses.
#include "shared/text_print.hpp"
// @ref ?Set_unknown_20@BitFontClass@@QAEXH@Z=004318d0
// @ref ?Print_Box@BitTextClass@@QAE_NPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490

bool BitTextClass::Print_Box_Bold(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y,
                                  int width, int height, int arg8, int arg9, int arg10)
{
    if (font == 0) {
        return false;
    }
    font->Set_unknown_20(x);
    bool result;
    if (font->unknown_40) {
        font->unknown_2c = 2;
        Print_Box(font, surface, text, x, y, width, height, arg8, arg9, arg10);
        result = Print_Box(font, surface, text, x + 1, y, width, height, arg8, arg9, arg10);
        font->unknown_2c = 1;
    } else {
        result = Print_Box(font, surface, text, x, y, width, height, arg8, arg9, arg10);
    }
    return result;
}
