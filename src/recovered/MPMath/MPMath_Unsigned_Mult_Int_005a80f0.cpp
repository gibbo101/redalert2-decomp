// XMP_Unsigned_Mult_Int(digit *product, digit const *multiplicand, short multiplier, int precision) (0x005A80F0)
// Multiplies by a 16-bit value in 16-bit steps; returns 0.
#include "shared/mpmath.hpp"

int __fastcall XMP_Unsigned_Mult_Int(digit *product, digit const *multiplicand, short multiplier, int precision)
{
    unsigned short const *m2 = (unsigned short const *)multiplicand;
    unsigned short *pr = (unsigned short *)product;
    unsigned long carry = 0;
    for (int i = 0; i < precision * 2; i++) {
        unsigned long p = (((unsigned long)multiplier) * *m2) + carry;
        *pr = (unsigned short)p;
        carry = p >> 16;
        m2++;
        pr++;
    }
    return 0;
}
