// bool Wstring::Set(char const *string) (0x0076ED30)
// Replaces the contents with a copy of a C string (empty for null); true.
#include "shared/wstring.hpp"

bool Wstring::Set(char const *string)
{
    *this = string;
    return true;
}
