// Multi-precision fixed-point reciprocal; complete original005A8CF0.
#include "shared/mpmath.hpp"
int __fastcall XMP_Reciprocal(digit *quotient, digit const *divisor, int precision)
{
    digit remainder[MAX_UNIT_PRECISION];
    if (XMP_Test_Eq_Int(divisor, 0, precision)) return -1;
    XMP_Init(remainder, 0, precision);
    XMP_Init(quotient, 0, precision);
    unsigned int remaining_bits;
    int significant_digits = XMP_Significance(divisor, precision);
    if (significant_digits == 0) {
        remaining_bits = 0;
    } else {
        int bit_count = significant_digits * UNITSIZE;
        digit high_mask = UPPER_MOST_BIT;
        while (!(divisor[significant_digits - 1] & high_mask)) {
            high_mask >>= 1;
            --bit_count;
        }
        remaining_bits = bit_count;
    }
    digit output_mask = XMP_Bit_Mask(remaining_bits + 1);
    int output_digits = ((int)(remaining_bits + 1) + 31) / 32;
    XMP_Set_Bit(remainder, remaining_bits - 1);
    quotient += output_digits - 1;
    while (remaining_bits--) {
        XMP_Shift_Left_Bits(remainder, 1, precision);
        if (XMP_Compare(remainder, divisor, precision) >= 0) {
            XMP_Sub(remainder, remainder, divisor, false, precision);
            *quotient |= output_mask;
        }
        output_mask >>= 1;
        if (output_mask == 0) {
            output_mask = UPPER_MOST_BIT;
            --quotient;
        }
    }
    // Clear temporary multi-precision state after use (the library's burn-clear idiom).
    XMP_Init(remainder, 0, precision);
    return 0;
}
