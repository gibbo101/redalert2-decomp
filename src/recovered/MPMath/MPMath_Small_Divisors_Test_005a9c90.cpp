// XMP_Small_Divisors_Test(digit const *candidate, int precision) (0x005A9C90)
// False if any small prime divides the number.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Small_Divisors_Test(digit const *candidate, int precision)
{
    digit quotient[MAX_UNIT_PRECISION];

    for (unsigned short const *ptr = primeTable; ptr < &primeTable[sizeof(primeTable) / sizeof(primeTable[0])]; ptr++) {
        if (XMP_Unsigned_Div_Int(quotient, candidate, *ptr, precision) == 0) {
            return false;
        }
    }
    return true;
}
