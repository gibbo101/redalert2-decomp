// XMP_Rabin_Miller_Test(Straw &rng, digit const *w, int rounds, int precision) (0x005A9E10)
// Rabin-Miller probable-prime test with rounds random witnesses.
#include "shared/mpmath.hpp"

bool __fastcall XMP_Rabin_Miller_Test(Straw &rng, digit const *w, int rounds, int precision)
{
    digit wminus1[MAX_UNIT_PRECISION];
    XMP_Sub_Int(wminus1, w, 1, 0, precision);

    unsigned maxbitprecision = precision * sizeof(digit) * 8;
    unsigned a;
    for (a = 0; a < maxbitprecision; a++) {
        if (XMP_Test_Bit(wminus1, a)) {
            break;
        }
    }

    digit m[MAX_UNIT_PRECISION];
    XMP_Move(m, wminus1, precision);
    XMP_Shift_Right_Bits(wminus1, a, precision);

    for (int i = 0; i < rounds; i++) {
        digit b[MAX_UNIT_PRECISION];
        digit temp[MAX_UNIT_PRECISION];
        XMP_Init(temp, 2, precision);
        XMP_Randomize(b, rng, temp, wminus1, precision);

        digit z[MAX_UNIT_PRECISION];
        XMP_Exponent_Mod(z, b, m, w, precision);

        if (XMP_Test_Eq_Int(z, 1, precision) || XMP_Compare(z, wminus1, precision) == 0) {
            continue;   // passes this round
        }

        unsigned j;
        for (j = 1; j < a; j++) {
            digit t2[MAX_UNIT_PRECISION];
            XMP_Exponent_Mod(t2, z, temp, w, precision);

            if (XMP_Compare(t2, wminus1, precision) == 0) {
                break;  // passed this round
            }
            if (XMP_Test_Eq_Int(z, 1, precision)) {
                return false;
            }
        }
        if (j == a) {
            return false;
        }
    }
    return true;
}
