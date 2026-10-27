// XMP_Inverse_A_Mod_B(digit *result, digit const *number, digit const *modulus, int precision) (0x005A8AA0)
// Multiplicative inverse of number modulo modulus (extended Euclid with
// three rotating remainders); result doubles as scratch.
#include "shared/mpmath.hpp"

void __fastcall XMP_Inverse_A_Mod_B(digit *result, digit const *number, digit const *modulus, int precision)
{
    digit g[3][MAX_UNIT_PRECISION];
    digit v[3][MAX_UNIT_PRECISION];
    digit y[MAX_UNIT_PRECISION];

    XMP_Move(g[0], modulus, precision);
    XMP_Move(g[1], number, precision);
    XMP_Init(v[0], 0, precision);
    XMP_Init(v[1], 1, precision);

    int i;
    for (i = 1; !XMP_Test_Eq_Int(g[i % 3], 0, precision); i++) {
        XMP_Unsigned_Div(g[(i + 1) % 3], y, g[(i - 1) % 3], g[i % 3], precision);
        XMP_Unsigned_Mult(result, v[i % 3], y, precision);
        XMP_Sub(v[(i + 1) % 3], v[(i - 1) % 3], result, 0, precision);
    }

    if (XMP_Is_Negative(v[(i - 1) % 3], precision)) {
        XMP_Add(v[(i - 1) % 3], v[(i - 1) % 3], modulus, 0, precision);
    }

    XMP_Move(result, v[(i - 1) % 3], precision);
}
