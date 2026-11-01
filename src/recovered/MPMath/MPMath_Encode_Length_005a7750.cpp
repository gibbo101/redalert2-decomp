// XMP_Encode(unsigned char *to, unsigned tobytes, digit const *from, int precision) (0x005A7750)
// Big-endian encoding into exactly tobytes bytes, sign-filled on the left; returns tobytes.
#include "shared/mpmath.hpp"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

unsigned __fastcall XMP_Encode(unsigned char *to, unsigned tobytes, digit const *from, int precision)
{
    unsigned frombytes = precision * sizeof(digit);
    unsigned char filler = (unsigned char)(XMP_Is_Negative(from, precision) ? 0xff : 0);

    unsigned index;
    for (index = 0; index < (tobytes - frombytes); index++) {
        *to++ = filler;
    }

    unsigned char const *fptr = ((unsigned char const *)from) + MIN(tobytes, frombytes);
    for (index = 0; index < MIN(tobytes, frombytes); index++) {
        *to++ = *--fptr;
    }

    return tobytes;
}
