// void ProgressScreenClass::Draw_Name(Point2D xy, wchar_t const *name, ColorScheme *scheme, int width) (0x0061FB70)
// Prints a player's name in the progress font, clipped to the name column
// (width -1: the width of fifteen "W"s).
#include "shared/progress_screen.hpp"
#include "shared/text_print.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??_C@_01FJFF@W?$AA@=007db208
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690

void ProgressScreenClass::Draw_Name(Point2D xy, wchar_t const *name, ColorScheme *scheme, int width)
{
    int text_width, text_height;
    Text_Size(&text_width, &text_height);
    if (width != -1) {
        text_width = width;
    }
    Rect clip(0, 0, xy.X + text_width, xy.Y + text_height);
    Fancy_Text_Printf(name, unknown_surface_839954, &clip, &xy, scheme, 0, 0x19);
}
