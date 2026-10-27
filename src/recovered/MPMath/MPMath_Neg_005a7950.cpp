// XMP_Neg(digit *number, int precision) (0x005A7950)
// Two's complement negation.
#include "shared/mpmath.hpp"

void __fastcall XMP_Neg(digit *number, int precision)
{
    XMP_Not(number, precision);
    XMP_Inc(number, precision);
}
