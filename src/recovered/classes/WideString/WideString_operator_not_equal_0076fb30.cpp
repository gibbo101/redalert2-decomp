#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref _wcsncat=00784704
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);

bool WideString::operator!=(WideString const &other) const
{
    if (Buffer == 0 && other.Buffer == 0) {
        return false;
    }
    if (Buffer == 0 || other.Buffer == 0) {
        return true;
    }
    if (wcscmp(Buffer, other.Buffer) != 0) {
        return true;
    }
    return false;
}
