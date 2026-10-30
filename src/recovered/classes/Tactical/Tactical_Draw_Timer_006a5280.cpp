// void __fastcall Draw_Timer(int line, ColorScheme *scheme, int value,
// wchar_t const *text, unsigned __int64 *flash_time, bool *flash) (0x006A5280): the
// timer captions Render draws above the bottom right corner of the tactical
// view, one per line: the text and the time left (seconds at 60 a minute,
// hours shown only when present). At zero the caption flashes white, its
// state flipping once a second (name and parameters hypotheses).
#include "shared/tactical.hpp"
#include "shared/text_print.hpp"
#include "shared/color_scheme.hpp"
#include "shared/audio.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??_C@_1CC@MCKI@?$AA?$CF?$AAs?$AA?5?$AA?5?$AA?$CF?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?$AA@=007f6ab4
// @ref ??_C@_1BM@JCCC@?$AA?$CF?$AAs?$AA?5?$AA?5?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?$AA@=007f6a98
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

void __fastcall Draw_Timer(int line, ColorScheme *scheme, int value, wchar_t const *text,
                                  unsigned __int64 *flash_time, bool *flash)
{
    wchar_t buffer[256];
    BitFontClass *font = Font_For_Style(0x4618);

    int hours = value / 60 / 60;
    int seconds = value % 60;
    int minutes = value / 60 % 60;
    if (hours) {
        swprintf(buffer, L"%s  %d:%02d:%02d", text, hours, minutes, seconds);
    } else {
        swprintf(buffer, L"%s  %02d:%02d", text, minutes, seconds);
    }

    if (value == 0 && flash_time && flash) {
        if (*flash_time <= Audio_Now()) {
            *flash_time = Audio_Now() + 1000;
            *flash = !*flash;
        }
        if (*flash) {
            scheme = ColorSchemes[0];
        }
    }

    Fancy_Text_Printf(buffer, unknown_surface_839964, &unknown_surface_839964->Get_Rect(),
        &Point2D(unknown_rect_839630.Width - 3, unknown_rect_839630.Height - (font->Height + 2) * (line + 1)), scheme, 0, 0x4618);
}
