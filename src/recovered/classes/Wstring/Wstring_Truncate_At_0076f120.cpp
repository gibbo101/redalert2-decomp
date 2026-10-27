// bool Wstring::Truncate_At(char character) (0x0076F120)
// Keeps the text before the first occurrence of character; false when there is none.
#include "shared/wstring.hpp"

bool Wstring::Truncate_At(char character)
{
    if (!Buffer) {
        return false;
    }
    char *found = strchr(Buffer, character);
    if (!found) {
        return false;
    }
    return Truncate(found - Buffer);
}
