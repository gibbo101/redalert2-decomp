// void WideString::Trim_Trailing(WideString const &characters) (0x00770230)
// Drops trailing characters found in characters (the counterpart of Trim_Leading
// 0x007701D0); the kept part goes through the inline Truncate.
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcsncpy=00783622
// @ref _wcschr=00783ac6
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcschr(unsigned short const *string, unsigned short character);

void WideString::Trim_Trailing(WideString const &characters)
{
    unsigned index = Length();
    while (index--) {
        if (!wcschr(characters.Get(), Buffer[index])) {
            break;
        }
    }
    Truncate(index + 1);
}
