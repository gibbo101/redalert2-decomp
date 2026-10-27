// Wstring &Wstring::operator+=(Wstring const &other) (0x0076DFC0)
// Appends another Wstring.
#include "shared/wstring.hpp"

Wstring &Wstring::operator+=(Wstring const &other)
{
    Concatenate(other);
    return *this;
}
