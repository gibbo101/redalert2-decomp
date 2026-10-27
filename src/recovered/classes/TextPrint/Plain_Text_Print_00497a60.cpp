// Point2D Plain_Text_Print(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy, unsigned fore, unsigned back, unsigned flags, ...) (0x00497A60)
// Formats the text (vswprintf) and prints it with Simple_Text_Print.
#include "shared/text_print.hpp"
// @ref _vswprintf=00783a58

Point2D __cdecl Plain_Text_Print(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy,
                                 unsigned fore, unsigned back, unsigned flags, ...)
{
    wchar_t buffer[512];
    if (format != 0) {
        vswprintf(buffer, format, (char *)(&flags + 1));
        return Simple_Text_Print(buffer, surface, clip, xy, fore, back, flags, 1);
    }
    return Simple_Text_Print(0, surface, clip, xy, fore, back, flags, 1);
}
