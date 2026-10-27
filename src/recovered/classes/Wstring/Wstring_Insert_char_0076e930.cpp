// bool Wstring::Insert(char character, unsigned position) (0x0076E930)
// Inserts one character at position (clamped to the length); a null string
// just takes the character.
#include "shared/wstring.hpp"

bool Wstring::Insert(char character, unsigned position)
{
    char text[2];
    if (!Buffer) {
        text[0] = character;
        text[1] = '\0';
        *this = text;
        return true;
    }
    unsigned length = strlen(Buffer);
    if (position > length) {
        position = length;
    }
    char *result = new char[length + 2];
    text[1] = '\0';
    char saved = Buffer[position];
    Buffer[position] = '\0';
    strcpy(result, Buffer);
    Buffer[position] = saved;
    text[0] = character;
    strcat(result, text);
    strcat(result, Buffer + position);
    delete[] Buffer;
    Buffer = result;
    return true;
}
