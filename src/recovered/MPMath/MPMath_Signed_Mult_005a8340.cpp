// XMP_Signed_Mult(digit *prod, digit const *multiplicand, digit const *multiplier, int precision) (0x005A8340)
// Signed multiplication through XMP_Unsigned_Mult on the absolute values; returns 0.
#include "shared/mpmath.hpp"

int __fastcall XMP_Signed_Mult(digit *prod, digit const *multiplicand, digit const *multiplier, int precision)
{
    if (XMP_Is_Negative(multiplicand, precision)) {
        digit abs_multiplicand[MAX_UNIT_PRECISION];
        XMP_Move(abs_multiplicand, multiplicand, precision);
        XMP_Neg(abs_multiplicand, precision);

        if (XMP_Is_Negative(multiplier, precision)) {
            digit abs_multiplier[MAX_UNIT_PRECISION];
            XMP_Move(abs_multiplier, multiplier, precision);
            XMP_Neg(abs_multiplier, precision);

            XMP_Unsigned_Mult(prod, abs_multiplicand, abs_multiplier, precision);
            XMP_Init(abs_multiplier, 0, precision);
        } else {
            XMP_Unsigned_Mult(prod, abs_multiplicand, multiplier, precision);
            XMP_Neg(prod, precision);
        }
        XMP_Init(abs_multiplicand, 0, precision);
    } else {
        if (XMP_Is_Negative(multiplier, precision)) {
            digit abs_multiplier[MAX_UNIT_PRECISION];
            XMP_Move(abs_multiplier, multiplier, precision);
            XMP_Neg(abs_multiplier, precision);

            XMP_Unsigned_Mult(prod, multiplicand, abs_multiplier, precision);
            XMP_Neg(prod, precision);
            XMP_Init(abs_multiplier, 0, precision);
        } else {
            XMP_Unsigned_Mult(prod, multiplicand, multiplier, precision);
        }
    }
    return 0;
}
