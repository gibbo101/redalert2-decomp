// XMP_Add_Int(result, left, digit right, carry, precision) (0x005A7E00)
#include "shared/mpmath.hpp"

bool __fastcall XMP_Add_Int(digit *result, digit const *left, digit right, bool carry, int precision)
{
    while (precision--) {
        digit term = *left + right;
        digit final = term + carry;
        carry = (term < *left || (carry && final == 0));

        right = 0;
        left++;
        *result++ = final;
    }
    return carry;
}
