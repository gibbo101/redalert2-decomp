// Point2D Fancy_Text_Printf(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy, ColorScheme *scheme, unsigned back, unsigned flags, ...) (0x00497B40)
// Formats the text (vswprintf) and prints it in the scheme's base colour.
#include "shared/text_print.hpp"
// @ref _vswprintf=00783a58
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050

Point2D __cdecl Fancy_Text_Printf(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy,
                                  ColorScheme *scheme, unsigned back, unsigned flags, ...)
{
    wchar_t buffer[512];
    if (format != 0) {
        vswprintf(buffer, format, (char *)(&flags + 1));
        return Scheme_Text_Print(buffer, surface, clip, xy, scheme, back, flags, 1);
    }
    return Scheme_Text_Print(0, surface, clip, xy, scheme, back, flags, 1);
}
