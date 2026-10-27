// Wstring Wstring::operator+(Wstring const &other) const (0x0076E1C0)
// New string: this followed by another Wstring.
#include "shared/wstring.hpp"

Wstring Wstring::operator+(Wstring const &other) const
{
    Wstring result(*this);
    result.Concatenate(other);
    return result;
}
