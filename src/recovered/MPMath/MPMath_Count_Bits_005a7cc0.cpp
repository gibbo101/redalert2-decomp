// XMP_Count_Bits(digit const *number, int precision) (0x005A7CC0)
// Bits up to and including the highest set bit.
#include "shared/mpmath.hpp"

int __fastcall XMP_Count_Bits(digit const *number, int precision)
{
    int sigdigits = XMP_Significance(number, precision);
    if (!sigdigits) {
        return 0;
    }

    int bits = sigdigits * UNITSIZE;
    number += sigdigits - 1;
    digit bitmask = UPPER_MOST_BIT;
    while (!(*number & bitmask)) {
        bitmask >>= 1;
        bits--;
    }
    return bits;
}
