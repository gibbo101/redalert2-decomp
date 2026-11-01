// XMP_Randomize(digit *result, Straw &rng, digit const *minval, digit const *maxval, int precision) (0x005AA1A0)
// A random number in [minval, maxval].
#include "shared/mpmath.hpp"

void __fastcall XMP_Randomize(digit *result, Straw &rng, digit const *minval, digit const *maxval, int precision)
{
    digit range[MAX_UNIT_PRECISION];
    XMP_Sub(range, maxval, minval, 0, precision);
    unsigned bit_count = XMP_Count_Bits(range, precision);
    do {
        XMP_Randomize(result, rng, bit_count, precision);
    } while (XMP_Compare(result, range, precision) > 0);

    XMP_Add(result, result, minval, 0, precision);
}
