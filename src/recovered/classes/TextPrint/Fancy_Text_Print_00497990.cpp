// Point2D Fancy_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy, ColorScheme *scheme, unsigned back, unsigned flags, int unknown8) (0x00497990)
// Simple_Text_Print in the base colour of a colour scheme.
#include "shared/text_print.hpp"
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc

Point2D __fastcall Fancy_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy,
                                    ColorScheme *scheme, unsigned back, unsigned flags, int unknown8)
{
    RGBClass color = scheme->BaseColor.To_RGB();
    unsigned pixel = ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
                   | ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
                   | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
    return Simple_Text_Print(text, surface, clip, xy, pixel, back, flags, unknown8);
}
