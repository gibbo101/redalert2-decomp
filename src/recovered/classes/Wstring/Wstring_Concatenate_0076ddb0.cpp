// bool Wstring::Concatenate(unsigned length, char const *string) (0x0076DDB0)
// Appends at most `length` characters (strncat).
// @ref _strncat=00784750
#include "shared/wstring.hpp"

bool Wstring::Concatenate(unsigned length, char const *string)
{
    char *old = Buffer;
    unsigned size = length + 1;
    if (old) {
        size += strlen(old);
    }
    Buffer = new char[size];
    if (old) {
        strcpy(Buffer, old);
    } else {
        Buffer[0] = '\0';
    }
    if (string) {
        strncat(Buffer, string, length);
    }
    if (old) {
        delete[] old;
    }
    return true;
}
