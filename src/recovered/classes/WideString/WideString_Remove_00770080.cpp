#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

short WideString::Remove(int position, int count)
{
    int length = wcslen(Buffer);
    if (position + count > length) {
        position = length - count;
    }
    if (position < 0) {
        count += position;
        position = 0;
    }
    if (count <= 0) {
        return 0;
    }
    unsigned short *result = new unsigned short[length - count + 1];
    Buffer[position] = 0;
    Buffer[position + count - 1] = 0;
    wcscpy(result, Buffer);
    wcscat(result, Buffer + position + count);
    delete Buffer;
    Buffer = result;
    return 1;
}
