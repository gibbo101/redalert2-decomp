// XMP_Abs(digit *number, int precision) (0x005A7980)
#include "shared/mpmath.hpp"

void __fastcall XMP_Abs(digit *number, int precision)
{
    if (XMP_Is_Negative(number, precision)) {
        XMP_Neg(number, precision);
    }
}
