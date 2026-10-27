// char const *Wstring::Get() const (0x0076E6F0)
// The text, or the empty string when null.
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

char const *Wstring::Get() const
{
    return Buffer ? Buffer : "";
}
