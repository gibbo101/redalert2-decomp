// XMP_Add(result, left, right, carry, precision) (0x005A7D90)
// result = left + right + carry; returns the carry out.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Add(digit *result, digit const *left, digit const *right, bool carry, int precision)
{
    while (precision--) {
        digit term = *left + *right;
        digit final = term + carry;
        carry = (term < *left || (carry && final == 0));

        right++;
        left++;
        *result++ = final;
    }
    return carry;
}
