// XMP_Fermat_Test(digit const *candidate, unsigned rounds, int precision) (0x005A9CE0)
// Fermat test with the first rounds small primes as witnesses.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Fermat_Test(digit const *candidate, unsigned rounds, int precision)
{
    digit term[MAX_UNIT_PRECISION];
    XMP_Move(term, candidate, precision);
    XMP_Dec(term, precision);

    for (unsigned i = 0; i < rounds; i++) {
        digit result[MAX_UNIT_PRECISION];
        digit small[MAX_UNIT_PRECISION];
        XMP_Init(small, primeTable[i], precision);
        XMP_Exponent_Mod(result, small, term, candidate, precision);
        if (!XMP_Test_Eq_Int(result, 1, precision)) {
            return false;
        }
    }
    return true;
}
