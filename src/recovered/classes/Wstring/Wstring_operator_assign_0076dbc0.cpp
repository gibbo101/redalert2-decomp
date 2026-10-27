// Wstring &Wstring::operator=(char const *string) (0x0076DBC0)
// Replaces the contents with a copy of a C string (empty for null).
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

Wstring &Wstring::operator=(char const *string)
{
    Release();
    Buffer = new char[string ? strlen(string) + 1 : 1];
    Buffer[0] = '\0';
    if (string) {
        strcpy(Buffer, string);
    }
    return *this;
}
