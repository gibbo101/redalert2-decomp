// char const *ThemeClass::Theme_File_Name(ThemeType theme) -- 0x006E8110 (name after Tiberian Sun)
// Purpose: the theme's sound file name (Sound + ".WAV") in a static buffer; "" for a theme out of range.
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"
// @ref __makepath=007831f0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04KFC@?4WAV?$AA@=007f8338
// @ref _?name@?1??Theme_File_Name@ThemeClass@@QAEPBDH@Z@4PADA=00ac0858

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

char const *ThemeClass::Theme_File_Name(ThemeType theme)
{
    static char name[256 + 256];

    if ((unsigned)theme < (unsigned)Themes.Count()) {
        _makepath(name, 0, 0, Themes[theme]->Sound, ".WAV");
        return name;
    }
    return "";
}
