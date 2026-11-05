// Primality filter and two Fermat witnesses (0x005AA380).
#include "shared/mpmath.hpp"
static inline bool Test_Fermat_Witness_Range(digit const *number,unsigned short const *first,unsigned short const *last,int precision)
{
digit term[MAX_UNIT_PRECISION];
    XMP_Move(term,number,precision);
    XMP_Dec(term,precision);
    for (unsigned short const *witness = first; witness < last; ++witness) {
        digit result[MAX_UNIT_PRECISION];
        digit small[MAX_UNIT_PRECISION];
        XMP_Init(small,*witness,precision);
        XMP_Exponent_Mod(result,small,term,number,precision);
        if (!XMP_Test_Eq_Int(result,1,precision)) return false;
    }
    return true;
}
bool __fastcall XMP_Is_Prime(digit const *number,int precision)
{
    if (!(*number & 1)) return false;
    if (XMP_Is_Small_Prime(number,precision)) return true;
    if (!XMP_Small_Divisors_Test(number,precision)) return false;
    if (!Test_Fermat_Witness_Range(number,primeTable,&primeTable[2],precision)) return false;
    return true;
}
