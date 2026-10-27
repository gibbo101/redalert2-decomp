// int Text_Lines(wchar_t const *text, int style, int columns, int *width, int *height) (0x004977D0)
// Measures text wrapped to the pixel width of `columns` 'W' characters in
// the style's font: the text area goes to width/height, the line count is
// returned (0 for no text or no font).
#include "shared/text_print.hpp"
// @ref ?Get_Text_Area@BitFontClass@@QAEXPBGPAH1H@Z=004314b0
// @ref ?Char_Pixel_Width@BitFontClass@@QBEHG@Z=00432170
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8

int __fastcall Text_Lines(wchar_t const *text, int style, int columns, int *width, int *height)
{
    *width = 0;
    *height = 0;
    BitFontClass *font = Font_For_Style(style);
    if (text != 0 && font != 0) {
        font->Get_Text_Area(text, width, height, font->Char_Pixel_Width(L'W') * columns);
        return *height / font->Height;
    }
    return 0;
}
