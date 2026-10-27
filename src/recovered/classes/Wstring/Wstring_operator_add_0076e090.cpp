// Wstring Wstring::operator+(char const *string) const (0x0076E090)
// New string: this followed by a C string.
#include "shared/wstring.hpp"

Wstring Wstring::operator+(char const *string) const
{
    Wstring result(*this);
    result.Concatenate(string);
    return result;
}
