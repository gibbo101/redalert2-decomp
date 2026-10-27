// memrev(char *buffer, unsigned int length) (0x005A9BD0)
// Reverses a byte buffer in place (unused).
#include "shared/mpmath.hpp"

void __fastcall memrev(char *buffer, unsigned int length)
{
    char *r2 = &(buffer[length - 1]);
    while (buffer < r2) {
        char b = *buffer;
        *buffer++ = *r2;
        *r2-- = b;
    }
}
