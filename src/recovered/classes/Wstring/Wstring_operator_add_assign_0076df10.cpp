// Wstring &Wstring::operator+=(char const *string) (0x0076DF10)
// Appends a C string.
#include "shared/wstring.hpp"

Wstring &Wstring::operator+=(char const *string)
{
    Concatenate(string);
    return *this;
}
