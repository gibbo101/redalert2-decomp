// bool WideString::operator==(unsigned short const *string) const (0x0076FA70)
#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3

extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);

bool WideString::operator==(unsigned short const *string) const
{
    if (Buffer == 0 && string == 0) {
        return true;
    }
    if (Buffer != 0 && string != 0) {
        return wcscmp(Buffer, string) == 0 ? true : false;
    }
    return false;
}
