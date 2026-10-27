#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref _wcschr=00783ac6
// @ref _memmove=00783290
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcschr(unsigned short const *string, unsigned short character);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

bool WideString::Remove_Character(unsigned short character)
{
    bool removed = false;
    if (!Buffer) {
        return false;
    }
    int length = wcslen(Buffer);
    unsigned short *found;
    while ((found = wcschr(Buffer, character)) != 0) {
        removed = true;
        memmove(found, found + 1, length * 2 - (found - Buffer) - 2);
        length--;
        Buffer[length] = 0;
    }
    if (removed) {
        unsigned short *result = new unsigned short[wcslen(Buffer) + 1];
        wcscpy(result, Buffer);
        delete Buffer;
        Buffer = result;
    }
    return removed;
}
