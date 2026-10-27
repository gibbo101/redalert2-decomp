// bool WideString::operator==(WideString const &other) const (0x0076FAB0)
#include "shared/wide_string.hpp"
// @ref _wcscmp=007837d3

extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);

bool WideString::operator==(WideString const &other) const
{
    if (Buffer == 0 && other.Buffer == 0) {
        return true;
    }
    if (Buffer != 0 && other.Buffer != 0) {
        return wcscmp(Buffer, other.Buffer) == 0 ? true : false;
    }
    return false;
}
