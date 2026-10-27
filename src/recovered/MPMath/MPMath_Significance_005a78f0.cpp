// XMP_Significance(digit const *number, int precision) (0x005A78F0)
// Number of digits up to the highest non-zero one.
#include "shared/mpmath.hpp"

int __fastcall XMP_Significance(digit const *number, int precision)
{
    number += precision - 1;
    while (!*number) {
        if (!--precision) {
            break;
        }
        number--;
    }
    return precision;
}
