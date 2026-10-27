// XMP_Unsigned_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision) (0x005A8670)
// Bitwise long division; returns -1 for a zero divisor, else 0.
#include "shared/mpmath.hpp"

int __fastcall XMP_Unsigned_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision)
{
    if (XMP_Test_Eq_Int(divisor, 0, precision)) {
        return -1;
    }

    XMP_Init(remainder, 0, precision);
    XMP_Init(quotient, 0, precision);

    int bits = XMP_Count_Bits(dividend, precision);
    int digits = (bits + UNITSIZE - 1) / UNITSIZE;
    if (!digits) {
        return 0;
    }

    digit const *dividend_ptr = &dividend[digits - 1];
    digit *quotient_ptr = &quotient[digits - 1];
    digit bitmask = (bits == 0) ? 0 : (1L << ((bits - 1) % UNITSIZE));

    for (int remaining = bits; remaining != 0; remaining--) {
        XMP_Shift_Left_Bits(remainder, 1, precision);
        if ((*dividend_ptr) & bitmask) {
            XMP_Inc(remainder, precision);
        }
        if (XMP_Compare(remainder, divisor, precision) >= 0) {
            XMP_Sub(remainder, remainder, divisor, 0, precision);
            *quotient_ptr |= bitmask;
        }

        bitmask >>= 1;
        if (!bitmask) {
            bitmask = UPPER_MOST_BIT;
            dividend_ptr--;
            quotient_ptr--;
        }
    }
    return 0;
}
