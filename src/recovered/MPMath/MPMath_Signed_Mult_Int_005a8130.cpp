// XMP_Signed_Mult_Int(digit *product, digit const *multiplicand, signed short multiplier, int precision) (0x005A8130)
// Signed multiplication by a 16-bit value; returns 0.
#include "shared/mpmath.hpp"

int __fastcall XMP_Signed_Mult_Int(digit *product, digit const *multiplicand, signed short multiplier, int precision)
{
    if (XMP_Is_Negative(multiplicand, precision)) {
        digit abs_multiplicand[MAX_UNIT_PRECISION];
        XMP_Move(abs_multiplicand, multiplicand, precision);
        XMP_Neg(abs_multiplicand, precision);

        if (multiplier < 0) {
            multiplier = (signed short)-multiplier;
            XMP_Unsigned_Mult_Int(product, abs_multiplicand, multiplier, precision);
        } else {
            XMP_Unsigned_Mult_Int(product, abs_multiplicand, multiplier, precision);
            XMP_Neg(product, precision);
        }
    } else {
        if (multiplier < 0) {
            multiplier = (signed short)-multiplier;
            XMP_Unsigned_Mult_Int(product, multiplicand, multiplier, precision);
            XMP_Neg(product, precision);
        } else {
            XMP_Unsigned_Mult_Int(product, multiplicand, multiplier, precision);
        }
    }
    return 0;
}
