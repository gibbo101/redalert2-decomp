// XMP_Inc(digit *number, int precision) (0x005A7910)
#include "shared/mpmath.hpp"

void __fastcall XMP_Inc(digit *number, int precision)
{
    while (!++(*number)) {
        number++;
        if (!--precision) {
            break;
        }
    }
}
