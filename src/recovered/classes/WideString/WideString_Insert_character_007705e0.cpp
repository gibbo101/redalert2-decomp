// bool WideString::Insert(unsigned short character, unsigned position) (0x007705E0)
// Inserts one character at position (clamped to the length).
#include "shared/wide_string.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);

bool WideString::Insert(unsigned short character, unsigned position)
{
    unsigned short text[2];
    if (Buffer == 0) {
        text[0] = character;
        text[1] = 0;
        *this = text;
        return true;
    }
    unsigned length = wcslen(Buffer);
    if (position > length) {
        position = length;
    }
    unsigned short *buffer = new unsigned short[length + 2];
    text[0] = Buffer[position];
    Buffer[position] = 0;
    text[1] = 0;
    wcscpy(buffer, Buffer);
    Buffer[position] = text[0];
    text[0] = character;
    wcscat(buffer, text);
    wcscat(buffer, Buffer + position);
    delete Buffer;
    Buffer = buffer;
    return true;
}
