// Rect Text_Rect(wchar_t const *text, int x, int y, unsigned flags, int padx, int pady) (0x00497360)
// The box text would occupy at x, y in the current font (flag 0x100 centres
// it on x, 0x200 right-aligns it), grown by padx/pady on each side.
#include "shared/text_print.hpp"
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690

Rect __fastcall Text_Rect(wchar_t const *text, int x, int y, unsigned flags, int padx, int pady)
{
    BitFontClass *font = BitFont;
    int width = font->String_Pixel_Width(text, 0);
    int height = font->Height;
    int left = x;
    if (flags & 0x100) {
        left = x - width / 2;
    } else if (flags & 0x200) {
        left = x - width;
    }
    return Rect(left - padx, y - pady, width + padx * 2, height + pady * 2);
}
