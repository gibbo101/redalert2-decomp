// XMP_Unsigned_Div_Int(digit *quotient, digit const *dividend, unsigned short divisor, int precision) (0x005A8540)
// Long division by a 16-bit value; returns the remainder (0 for a zero
// divisor).
#include "shared/mpmath.hpp"

unsigned short __fastcall XMP_Unsigned_Div_Int(digit *quotient, digit const *dividend, unsigned short divisor, int precision)
{
    if (!divisor) {
        return 0;
    }

    unsigned short remainder = 0;
    XMP_Init(quotient, 0, precision);

    int bits = XMP_Count_Bits(dividend, precision);
    int digits = (bits + UNITSIZE - 1) / UNITSIZE;
    digit const *dividend_ptr = &dividend[digits - 1];
    if (!digits) {
        return 0;
    }

    digit bitmask = (bits == 0) ? 0 : (1L << ((bits - 1) % UNITSIZE));
    digit *quotient_ptr = &quotient[digits - 1];

    for (int remaining = bits; remaining--; ) {
        remainder <<= 1;
        if ((*dividend_ptr) & bitmask) {
            remainder++;
        }
        if (remainder >= divisor) {
            remainder -= divisor;
            *quotient_ptr |= bitmask;
        }

        bitmask >>= 1;
        if (!bitmask) {
            bitmask = UPPER_MOST_BIT;
            dividend_ptr--;
            quotient_ptr--;
        }
    }
    return remainder;
}
