// XMP_Shift_Right_Bits(digit *number, int bits, int precision) (0x005A79C0)
// Logical right shift.
#include "shared/mpmath.hpp"

void __fastcall XMP_Shift_Right_Bits(digit *number, int bits, int precision)
{
    if (bits == 0) {
        return;
    }

    if (bits == UNITSIZE) {
        number += precision;
        digit carry = 0;
        while (precision--) {
            number--;
            digit temp = *number;
            *number = carry;
            carry = temp;
        }
        return;
    }

    if (bits < UNITSIZE) {
        number += precision;
        digit carry = 0;
        digit mask = (1L << bits) - 1;
        int nbits = UNITSIZE - bits;
        while (precision--) {
            number--;
            digit temp = *number & mask;
            *number >>= bits;
            *number |= carry << nbits;
            carry = temp;
        }
        return;
    }

    int digits_to_shift = bits / UNITSIZE;
    int bits_to_shift = bits % UNITSIZE;
    int index;
    for (index = digits_to_shift; index < (precision - 1); index++) {
        *number = (*(number + digits_to_shift) >> bits_to_shift) |
                  (*(number + (digits_to_shift + 1)) << (UNITSIZE - bits_to_shift));
        number++;
    }
    if (digits_to_shift < precision) {
        *number = (*(number + digits_to_shift) >> bits_to_shift);
        number++;
    }
    for (index = 0; index < (digits_to_shift < precision ? digits_to_shift : precision); index++) {
        *number++ = 0;
    }
}
