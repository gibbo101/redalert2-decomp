// Point2D unknown_scheme_text_print_498050(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy, unsigned fore, unsigned back, unsigned flags, int scheme, int unknown8) (0x00498050)
// Simple_Text_Print in the base colour of colour scheme `scheme` (an index
// into ColorSchemes), or in `fore` when scheme is -1.
#include "shared/text_print.hpp"
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

Point2D __fastcall unknown_scheme_text_print_498050(wchar_t const *text, Surface *surface, Rect const *clip,
                                                    Point2D *xy, unsigned fore, unsigned back, unsigned flags,
                                                    int scheme, int unknown8)
{
    if (scheme == -1) {
        return Simple_Text_Print(text, surface, clip, xy, fore, back, flags, unknown8);
    }
    return Scheme_Text_Print(text, surface, clip, xy, ColorSchemes[scheme], back, flags, unknown8);
}
