// XMP_Compare(digit const *left, digit const *right, int precision) (0x005A7D40)
// Unsigned comparison: -1, 0 or 1.
#include "shared/mpmath.hpp"

int __fastcall XMP_Compare(digit const *left, digit const *right, int precision)
{
    left += (precision - 1);
    right += (precision - 1);
    do {
        if (*left < *right) {
            return -1;
        }
        if (*left > *right) {
            return 1;
        }
        left--;
        right--;
    } while (--precision);
    return 0;
}
