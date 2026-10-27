// XMP_Unsigned_Decode(digit *result, unsigned char const *from, int frombytes, int precision) (0x005A78B0)
// Reads big-endian unsigned bytes, zero-extending.
#include "shared/mpmath.hpp"

void __fastcall XMP_Unsigned_Decode(digit *result, unsigned char const *from, int frombytes, int precision)
{
    int fillcount = precision * sizeof(digit) - frombytes;
    unsigned char *dest = (unsigned char *)&result[precision];

    while (fillcount > 0) {
        *--dest = 0;
        fillcount--;
    }
    while (frombytes > 0) {
        *--dest = *from++;
        frombytes--;
    }
}
