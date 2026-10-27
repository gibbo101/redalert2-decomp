// XMP_Dec(digit *number, int precision) (0x005A7930)
#include "shared/mpmath.hpp"

void __fastcall XMP_Dec(digit *number, int precision)
{
    while (--(*number) == (digit)~0UL) {
        number++;
        if (!--precision) {
            break;
        }
    }
}
