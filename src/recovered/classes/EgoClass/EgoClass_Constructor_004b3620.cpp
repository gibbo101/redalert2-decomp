#include "shared/ego.hpp"
extern "C" unsigned int __cdecl wcslen(wchar_t const *text);
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
EgoClass::EgoClass(int unknown04, int y, wchar_t const *text, unsigned int flags)
    : unknown_04(unknown04), Y(y), TextFlags(flags)
{
    Text = new wchar_t[wcslen(text) + 1];
    wcscpy(Text, text);
}
