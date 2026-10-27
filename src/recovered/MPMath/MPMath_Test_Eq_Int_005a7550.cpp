// XMP_Test_Eq_Int(digit const *number, int value, int precision) (0x005A7550)
// Whether the number equals a small non-negative value.
#include "shared/mpmath.hpp"

int __fastcall XMP_Test_Eq_Int(digit const *number, int value, int precision)
{
    return (*number == (digit)value) && XMP_Significance(number, precision) <= 1;
}
