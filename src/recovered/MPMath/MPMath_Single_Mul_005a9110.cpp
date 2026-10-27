// XMP_Single_Mul(unsigned short *prod, unsigned short const *multiplicand, unsigned short multiplier, int precision) (0x005A9110)
// prod += multiplicand * multiplier over precision 16-bit units, carrying
// into the unit above.
#include "shared/mpmath.hpp"

void __fastcall XMP_Single_Mul(unsigned short *prod, unsigned short const *multiplicand, unsigned short multiplier, int precision)
{
    unsigned long carry = 0;
    for (int i = 0; i < precision; i++) {
        unsigned long p = (unsigned long)multiplier * *multiplicand++;
        p += *prod + carry;
        *prod++ = (unsigned short)p;
        carry = p >> 16;
    }
    *prod += (unsigned short)carry;
}
