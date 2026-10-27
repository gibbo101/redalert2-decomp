// XMP_Sub(result, left, right, borrow, precision) (0x005A7E60)
// result = left - right - borrow in 16-bit steps; returns the borrow out.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Sub(digit *result, digit const *left, digit const *right, bool borrow, int precision)
{
    unsigned short const *left_ptr = (unsigned short const *)left;
    unsigned short const *right_ptr = (unsigned short const *)right;
    unsigned short *result_ptr = (unsigned short *)result;

    precision *= 2;
    while (precision--) {
        digit x = (digit)*left_ptr - (digit)*right_ptr - (digit)borrow;
        right_ptr++;
        left_ptr++;
        *result_ptr++ = (unsigned short)x;
        borrow = (((1L << 16) & x) != 0L);
    }
    return borrow;
}
