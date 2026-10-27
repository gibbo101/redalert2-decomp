// XMP_Rotate_Left(digit *number, bool carry, int precision) (0x005A7C40)
// Shifts left one bit taking carry in; returns the bit shifted out.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Rotate_Left(digit *number, bool carry, int precision)
{
    while (precision--) {
        bool temp = ((*number & UPPER_MOST_BIT) != 0);
        *number = (*number << 1);
        if (carry) {
            (*number)++;
        }
        carry = temp;
        number++;
    }
    return carry;
}
