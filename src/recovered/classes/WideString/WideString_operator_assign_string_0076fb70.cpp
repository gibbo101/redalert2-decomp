// WideString &WideString::operator=(unsigned short const *string) (0x0076FB70)
// Replaces the text with an owned copy (an empty string for null).
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b

extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);

WideString &WideString::operator=(unsigned short const *string)
{
    if (Buffer != 0) {
        delete Buffer;
    }
    Buffer = 0;
    int length = string != 0 ? wcslen(string) + 1 : 1;
    Buffer = new unsigned short[length];
    Buffer[0] = 0;
    if (string != 0) {
        wcscpy(Buffer, string);
    }
    return *this;
}
