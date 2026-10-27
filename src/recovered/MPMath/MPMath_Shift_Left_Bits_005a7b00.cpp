// XMP_Shift_Left_Bits(digit *number, int bits, int precision) (0x005A7B00)
#include "shared/mpmath.hpp"

void __fastcall XMP_Shift_Left_Bits(digit *number, int bits, int precision)
{
    if (bits == 0) {
        return;
    }

    if (bits == UNITSIZE) {
        digit carry = 0;
        while (precision--) {
            digit temp = *number;
            *number = carry;
            carry = temp;
            number++;
        }
        return;
    }

    if (bits < UNITSIZE) {
        digit carry = 0;
        digit mask = ~(((digit)~0UL) >> bits);
        int nbits = UNITSIZE - bits;
        while (precision--) {
            digit temp = *number & mask;
            *number <<= bits;
            *number |= carry >> nbits;
            carry = temp;
            number++;
        }
        return;
    }

    int digits_to_shift = bits / UNITSIZE;
    int bits_to_shift = bits % UNITSIZE;
    int index;
    number += precision - 1;
    for (index = digits_to_shift; index < (precision - 1); index++) {
        *number = (*(number - digits_to_shift) << bits_to_shift) |
                  (*(number - (digits_to_shift + 1)) >> (UNITSIZE - bits_to_shift));
        number--;
    }
    if (digits_to_shift < precision) {
        *number = (*(number - digits_to_shift) << bits_to_shift);
        number--;
    }
    for (index = 0; index < (digits_to_shift < precision ? digits_to_shift : precision); index++) {
        *number-- = 0;
    }
}
