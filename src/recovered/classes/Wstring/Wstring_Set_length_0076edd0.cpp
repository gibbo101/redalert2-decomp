// bool Wstring::Set(unsigned length, char const *string) (0x0076EDD0)
// Replaces the contents with at most length characters of string (strncpy
// into length + 1 bytes, always terminated); true.
#include "shared/wstring.hpp"

bool Wstring::Set(unsigned length, char const *string)
{
    Release();
    Buffer = new char[length + 1];
    Buffer[0] = '\0';
    if (string) {
        strncpy(Buffer, string, length);
    }
    Buffer[length] = '\0';
    return true;
}
