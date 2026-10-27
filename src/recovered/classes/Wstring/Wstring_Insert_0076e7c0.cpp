// bool Wstring::Insert(char const *string, unsigned position) (0x0076E7C0)
// Inserts a C string at position (clamped to the length); a null string
// just takes the text.
#include "shared/wstring.hpp"

bool Wstring::Insert(char const *string, unsigned position)
{
    if (!Buffer) {
        *this = string;
        return true;
    }
    if (position > strlen(Buffer)) {
        position = strlen(Buffer);
    }
    char *result = new char[strlen(Buffer) + strlen(string) + 1];
    memset(result, 0, strlen(Buffer) + strlen(string) + 1);
    strcpy(result, Buffer);
    memmove(result + position + strlen(string), result + position, strlen(Buffer) - position + 1);
    memmove(result + position, string, strlen(string));
    delete[] Buffer;
    Buffer = result;
    return true;
}
