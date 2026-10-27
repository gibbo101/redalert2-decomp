// Point2D Fancy_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy, ColorScheme *scheme, unsigned back, unsigned flags, unsigned width, int const *tabs) (0x00497E80)
// Conquer_Clip_Text_Print in the base colour of a colour scheme.
#include "shared/text_print.hpp"
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050

Point2D __fastcall Fancy_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip,
                                         Point2D *xy, ColorScheme *scheme, unsigned back, unsigned flags,
                                         unsigned width, int const *tabs)
{
    RGBClass color = scheme->BaseColor.To_RGB();
    unsigned pixel = ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
                   | ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
                   | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
    return Conquer_Clip_Text_Print(text, surface, clip, xy, pixel, back, flags, width, tabs);
}
