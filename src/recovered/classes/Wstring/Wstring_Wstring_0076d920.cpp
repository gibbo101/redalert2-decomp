// Wstring::Wstring(char const *string) : (0x0076D920)
// Copy of a C string (an empty string for null).
#include "shared/wstring.hpp"

Wstring::Wstring(char const *string) :
    Buffer(0)
{
    *this = string;
}
