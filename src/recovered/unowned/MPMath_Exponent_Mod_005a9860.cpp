// @ref ?XMP_Mod_Mult@@YIHPAKPBK1H@Z=005a9400
// Modular exponentiation by repeated squaring (0x005A9860).
#include "shared/mpmath.hpp"

int __fastcall XMP_Exponent_Mod(digit *result, digit const *base,
    digit const *exponent, digit const *modulus, int precision)
{
    digit product[MAX_UNIT_PRECISION];
    XMP_Init(result, 1, precision);
    if (XMP_Test_Eq_Int(exponent, 0, precision)) {
        if (XMP_Test_Eq_Int(base, 0, precision)) return -1;
        return 0;
    }
    if (XMP_Test_Eq_Int(modulus, 0, precision)) return -2;
    if (XMP_Compare(base, modulus, precision) >= 0) return -3;
    if (XMP_Compare(exponent, modulus, precision) >= 0) return -4;

    int used = XMP_Significance(modulus, precision);
    if (XMP_Prepare_Modulus(modulus, used)) return -5;
    int bits = XMP_Count_Bits(exponent, used);
    int digits = (bits + 31) / 32;
    if (!digits) return 0;
    digit mask = XMP_Bit_Mask(bits);
    exponent += digits - 1;
    int remaining = bits - 1;
    XMP_Move(result, base, used);
    mask >>= 1;
    if (!mask) {
        mask = UPPER_MOST_BIT;
        --exponent;
    }
    while (remaining--) {
        XMP_Mod_Mult(product, result, result, used);
        if (*exponent & mask) XMP_Mod_Mult(result, product, base, used);
        else XMP_Move(result, product, used);
        mask >>= 1;
        if (!mask) {
            mask = UPPER_MOST_BIT;
            --exponent;
        }
    }
    XMP_Init(product, 0, used);
    XMP_Mod_Mult_Clear(used);
    return 0;
}
