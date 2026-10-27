#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref _wcsncpy=00783622
// @ref _memmove=00783290
// @ref _memset=00783800
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
extern "C" int __cdecl tolower(int character);
extern "C" int __cdecl toupper(int character);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

bool WideString::Is_Narrow() const
{
    if (Buffer != 0) {
        int length = wcslen(Buffer);
        for (int index = 0; index < length; index++) {
            if (Buffer[index] >= 0x100) {
                return false;
            }
        }
    }
    return true;
}
