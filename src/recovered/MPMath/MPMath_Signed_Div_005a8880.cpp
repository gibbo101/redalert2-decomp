// XMP_Signed_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision) (0x005A8880)
// Floored signed division: a negative quotient is rounded down and the
// remainder takes the divisor's sign.
#include "shared/mpmath.hpp"

void __fastcall XMP_Signed_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision)
{
    bool negative = false;

    digit scratch_dividend[MAX_UNIT_PRECISION];
    XMP_Move(scratch_dividend, dividend, precision);

    digit scratch_divisor[MAX_UNIT_PRECISION];
    XMP_Move(scratch_divisor, divisor, precision);

    if (XMP_Is_Negative(scratch_dividend, precision)) {
        XMP_Neg(scratch_dividend, precision);
        negative = !negative;
    }

    if (XMP_Is_Negative(scratch_divisor, precision)) {
        XMP_Neg(scratch_divisor, precision);
        negative = !negative;
    }

    XMP_Unsigned_Div(remainder, quotient, scratch_dividend, scratch_divisor, precision);

    if (negative) {
        XMP_Neg(quotient, precision);
        if (!XMP_Test_Eq_Int(remainder, 0, precision)) {
            XMP_Dec(quotient, precision);
            XMP_Neg(remainder, precision);
            XMP_Add(remainder, remainder, scratch_divisor, 0, precision);
        }
    }
}
