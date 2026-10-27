// unsigned short const *WideString::Get() const (0x007703F0)
// The text, or an empty string when null.
#include "shared/wide_string.hpp"
// @ref ??_C@_11A@?$AA?$AA@=00839d4c

unsigned short const *WideString::Get() const
{
    return Buffer != 0 ? Buffer : (unsigned short const *)L"";
}
