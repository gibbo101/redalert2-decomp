// XMP_Randomize(digit *result, Straw &rng, int nbits, int precision) (0x005AA130)
// A random number of at most nbits bits drawn from rng.
#include "shared/mpmath.hpp"
#include "shared/straw.hpp"

void __fastcall XMP_Randomize(digit *result, Straw &rng, int nbits, int precision)
{
    if (nbits >= precision * (int)sizeof(digit) * 8) {
        nbits = precision * sizeof(digit) * 8;
    }

    unsigned nbytes = nbits / 8 + 1;
    XMP_Init(result, 0, precision);
    rng.Get(result, nbytes);
    ((unsigned char *)result)[nbytes - 1] &= ~((~0) << (nbits % 8));
}
