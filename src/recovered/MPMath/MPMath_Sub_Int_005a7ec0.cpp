// XMP_Sub_Int(result, left, unsigned short right, borrow, precision) (0x005A7EC0)
#include "shared/mpmath.hpp"

bool __fastcall XMP_Sub_Int(digit *result, digit const *left, unsigned short right, bool borrow, int precision)
{
    unsigned short const *left_ptr = (unsigned short const *)left;
    unsigned short *result_ptr = (unsigned short *)result;

    precision *= 2;
    while (precision--) {
        digit x = (digit)*left_ptr - (digit)right - (digit)borrow;
        left_ptr++;
        *result_ptr++ = (unsigned short)x;
        borrow = (((1L << 16) & x) != 0L);
        right = 0;
    }
    return borrow;
}
