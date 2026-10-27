// void Wstring::Copy_Padded(char *buffer, unsigned size) const (0x0076E6A0)
// Copies into a space-padded fixed field of `size` characters.
// @ref _strncpy=007823d0
#include "shared/wstring.hpp"

void Wstring::Copy_Padded(char *buffer, unsigned size) const
{
    unsigned length;
    strncpy(buffer, Buffer, size);
    length = strlen(Buffer);
    for (unsigned index = length; index < size; index++) {
        buffer[index] = ' ';
    }
    buffer[size] = '\0';
}
