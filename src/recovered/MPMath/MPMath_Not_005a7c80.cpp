// XMP_Not(digit *number, int precision) (0x005A7C80)
#include "shared/mpmath.hpp"

void __fastcall XMP_Not(digit *number, int precision)
{
    for (int index = 0; index < precision; index++) {
        *number = ~(*number);
        number++;
    }
}
