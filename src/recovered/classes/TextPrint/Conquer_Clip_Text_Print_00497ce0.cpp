// Point2D Conquer_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy, unsigned fore, unsigned back, unsigned flags, unsigned width, int const *tabs) (0x00497CE0)
// Prints tab-separated text, clipped to `width` pixels from xy: each field
// is printed with Simple_Text_Print; a tab advances to the next stop in
// `tabs` (or the next multiple-of-50 stop when there is no table). A field
// that does not fit is cut at the last whole character and ends printing.
// Returns where the last print ended (xy when nothing was printed).
#include "shared/text_print.hpp"
// @ref _wcscpy=00783689
// @ref _wcschr=00783ac6
// @ref ?Char_Pixel_Width@BitFontClass@@QBEHG@Z=00432170
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8

Point2D __fastcall Conquer_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip,
                                           Point2D *xy, unsigned fore, unsigned back, unsigned flags,
                                           unsigned width, int const *tabs)
{
    Point2D result = *xy;
    if (text != 0) {
        wchar_t buffer[512];
        wcscpy(buffer, text);
        BitFontClass *font = Font_For_Style(flags);
        wchar_t *source = buffer;
        unsigned offset = 0;
        int processing = 1;
        while (processing && offset < width) {
            wchar_t *tab = wcschr(source, L'\t');
            if (tab != 0) {
                *tab = 0;
            }
            if (*source != 0) {
                unsigned pixels = 0;
                wchar_t *p = source;
                do {
                    pixels += font->Char_Pixel_Width(*p++);
                } while (*p != 0 && offset + pixels < width);
                if (offset + pixels >= width) {
                    p--;
                    pixels -= font->Char_Pixel_Width(*p);
                    *p = 0;
                    processing = 0;
                }
                Point2D pos(xy->X + offset, xy->Y);
                result = Simple_Text_Print(source, surface, clip, &pos, fore, back, flags, 1);
                offset += pixels;
            }
            if (tab == 0) {
                break;
            }
            if (tabs != 0) {
                while (offset > (unsigned)*tabs) {
                    tabs++;
                }
                offset = *tabs;
            } else {
                offset = (offset + 1) * 50;
            }
            source = tab + 1;
        }
    }
    return result;
}
