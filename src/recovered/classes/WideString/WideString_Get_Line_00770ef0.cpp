#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref _strchr=00784130
// @ref _wcsncpy=00783622
// @ref _memmove=00783290
// @ref _memset=00783800
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??_C@_02PIMC@?$AN?6?$AA@=007d7cec
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
extern "C" int __cdecl tolower(int character);
extern "C" int __cdecl toupper(int character);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

int WideString::Get_Line(int start, WideString &line) const
{
    int position = start;
    if (start >= (int)Length()) {
        return -1;
    }
    while (position < (int)Length() && !strchr("\r\n", Buffer[position])) {
        position++;
    }
    int end = position;
    if (Buffer[position] == L'\r' && Buffer[position + 1] == L'\n') {
        position++;
        end = position;
    }
    line = Buffer + start;
    line.Truncate(end - start + 1);
    return end + 1;
}
