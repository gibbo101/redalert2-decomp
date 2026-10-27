// XMP_Signed_Decode(digit *result, unsigned char const *from, int frombytes, int precision) (0x005A7860)
// Reads big-endian two's complement bytes, sign-extending.
#include "shared/mpmath.hpp"

void __fastcall XMP_Signed_Decode(digit *result, unsigned char const *from, int frombytes, int precision)
{
    unsigned char fill = (unsigned char)((*from & 0x80) ? 0xFF : 0);
    int fillcount = precision * sizeof(digit) - frombytes;
    unsigned char *dest = (unsigned char *)&result[precision];

    while (fillcount > 0) {
        *--dest = fill;
        fillcount--;
    }
    while (frombytes > 0) {
        *--dest = *from++;
        frombytes--;
    }
}
