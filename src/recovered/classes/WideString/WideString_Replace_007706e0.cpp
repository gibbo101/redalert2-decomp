#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref _wcsstr=00785a1e
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
extern "C" unsigned short *__cdecl wcsstr(unsigned short const *string, unsigned short const *match);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
extern "C" int __cdecl tolower(int character);
extern "C" int __cdecl toupper(int character);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

bool WideString::Replace(unsigned short const *find, unsigned short const *with)
{
    WideString result;
    unsigned short const *current = Get();
    while (current != 0 && *current != 0) {
        unsigned short const *found = wcsstr(current, find);
        if (found == 0) {
            result.Concatenate(current);
            break;
        }
        int length = (int)found - (int)current;
        if (length != 0) {
            unsigned short *old = result.Buffer;
            unsigned size = length + 1;
            if (old != 0) {
                size += wcslen(old);
            }
            result.Buffer = new unsigned short[size * 2];
            if (old != 0) {
                wcscpy(result.Buffer, old);
            } else {
                result.Buffer[0] = 0;
            }
            wcsncat(result.Buffer, current, length);
            if (old != 0) {
                delete old;
            }
        }
        if (with != 0) {
            result.Concatenate(with);
        }
        current = (unsigned short const *)((int)found + wcslen(find) * 2);
        if (current == 0) {
            break;
        }
    }
    *this = (unsigned short const *)result;
    return true;
}
