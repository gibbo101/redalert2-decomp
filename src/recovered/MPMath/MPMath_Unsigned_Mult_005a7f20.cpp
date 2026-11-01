// XMP_Unsigned_Mult(digit *prod, digit const *multiplicand, digit const *multiplier, int precision) (0x005A7F20)
// Shift-and-add multiplication over the multiplier's significant bits; returns 0.
// XMP_Unsigned_Mult(digit *product, digit const *multiplicand, digit const *multiplier, int precision) (0x005A7F20)
// Shift-and-add multiplication; returns 0.
#include "shared/mpmath.hpp"

int __fastcall XMP_Unsigned_Mult(digit *product, digit const *multiplicand, digit const *multiplier, int precision)
{
    XMP_Init(product, 0, precision);

    if (XMP_Test_Eq_Int(multiplicand, 0, precision)) {
        return 0;
    }
    if (XMP_Test_Eq_Int(multiplier, 0, precision)) {
        return 0;
    }

    int bits = XMP_Count_Bits(multiplier, precision);
    digit bitmask = (bits == 0) ? 0 : (1L << ((bits - 1) % UNITSIZE));
    int digits = (bits + UNITSIZE - 1) / UNITSIZE;
    if (!digits) {
        return 0;
    }
    multiplier += digits;

    for (int remaining = bits; remaining != 0; remaining--) {
        XMP_Shift_Left_Bits(product, 1, precision);
        if ((*(multiplier - 1)) & bitmask) {
            XMP_Add(product, product, multiplicand, 0, precision);
        }
        bitmask >>= 1;
        if (!bitmask) {
            bitmask = UPPER_MOST_BIT;
            multiplier--;
        }
    }
    return 0;
}
