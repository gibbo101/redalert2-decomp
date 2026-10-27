// Wstring &Wstring::operator=(Wstring const &other) (0x0076DC30)
// Assignment; skipped when the strings already compare equal.
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

Wstring &Wstring::operator=(Wstring const &other)
{
    if (*this == other) {
        return *this;
    }
    *this = other.Get();
    return *this;
}
