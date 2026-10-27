// XMP_Double_Mul(digit *prod, digit const *multiplicand, digit const *multiplier, int precision) (0x005A9160)
// Double-precision product (prod holds 2 * precision digits).
#include "shared/mpmath.hpp"

void __fastcall XMP_Double_Mul(digit *prod, digit const *multiplicand, digit const *multiplier, int precision)
{
    XMP_Init(prod, 0, precision * 2);

    unsigned short const *multiplier_ptr = (unsigned short const *)multiplier;
    unsigned short *prod_ptr = (unsigned short *)prod;
    for (int i = 0; i < precision * 2; i++) {
        XMP_Single_Mul(prod_ptr++, (unsigned short const *)multiplicand, *multiplier_ptr++, precision * 2);
    }
}
