// XMP_Encode(unsigned char *to, digit const *from, int precision) (0x005A77F0)
// Writes the number as minimal two's complement big-endian bytes; returns
// the count. (The scan for the top byte starts precision BYTES into the
// number - original behaviour.)
#include "shared/mpmath.hpp"

// Not expanded into XMP_DER_Encode in the original; auto_inline(off)
// reproduces the call (hypothesis: the original was not inlinable there).
#pragma auto_inline(off)
int __fastcall XMP_Encode(unsigned char *to, digit const *from, int precision)
{
    bool is_negative = XMP_Is_Negative(from, precision);
    unsigned char filler = (unsigned char)(is_negative ? 0xFF : 0);

    unsigned char const *number_ptr = (unsigned char const *)from + precision - 1;
    while (number_ptr > (unsigned char const *)from && *number_ptr == filler) {
        number_ptr--;
    }

    int index = 0;
    if (((*number_ptr & 0x80) && !is_negative) || (!(*number_ptr & 0x80) && is_negative)) {
        to[index++] = filler;
    }

    to[index++] = *number_ptr;
    while (number_ptr != (unsigned char const *)from) {
        --number_ptr;
        to[index++] = *number_ptr;
    }
    return index;
}
#pragma auto_inline(on)
