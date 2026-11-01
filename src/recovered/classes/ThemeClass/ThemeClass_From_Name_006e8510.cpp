// int ThemeClass::From_Name(char const *name) const (0x006E8510)
// The theme whose INI name is name (case blind), or -1.
#define THEME_CONTROL_RECORD
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
// @ref __stricmp=00781f20

extern "C" unsigned int __cdecl strlen(char const *string);
#pragma intrinsic(strlen)
extern "C" int __cdecl _stricmp(char const *left, char const *right);

int ThemeClass::From_Name(char const *name) const
{
    if (name != 0 && strlen(name) > 0) {
        for (int theme = 0; theme < Themes.Count(); theme++) {
            if (_stricmp(Themes[theme]->Name, name) == 0) {
                return theme;
            }
        }
    }
    return THEME_NONE;
}
