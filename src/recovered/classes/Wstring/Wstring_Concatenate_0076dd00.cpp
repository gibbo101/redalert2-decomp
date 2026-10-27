// bool Wstring::Concatenate(char const *string) (0x0076DD00)
// Appends a C string.
#include "shared/wstring.hpp"

bool Wstring::Concatenate(char const *string)
{
    if (!string) {
        return true;
    }
    char *old = Buffer;
    unsigned size = strlen(string) + 1;
    if (old) {
        size += strlen(old);
    }
    Buffer = new char[size];
    if (old) {
        strcpy(Buffer, old);
    } else {
        Buffer[0] = '\0';
    }
    strcat(Buffer, string);
    if (old) {
        delete[] old;
    }
    return true;
}
