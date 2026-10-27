// bool Wstring::Remove_Character(char character) (0x0076E3E0)
// Deletes every occurrence of a character, then reallocates to fit.
// @ref _strchr=00784130
#include "shared/wstring.hpp"

bool Wstring::Remove_Character(char character)
{
    bool removed = false;
    if (!Buffer) {
        return false;
    }
    int length = strlen(Buffer);
    char *found;
    while ((found = strchr(Buffer, character)) != 0) {
        removed = true;
        memmove(found, found + 1, Buffer - found + length - 1);
        length--;
        Buffer[length] = '\0';
    }
    if (removed) {
        char *result = new char[strlen(Buffer) + 1];
        strcpy(result, Buffer);
        delete[] Buffer;
        Buffer = result;
    }
    return removed;
}
