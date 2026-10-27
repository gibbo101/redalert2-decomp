// XMP_Prepare_Modulus(digit const *modulus, int precision) (0x005A9220)
// Sets up Upton's modular reduction for a modulus: keeps a copy, its size,
// and a normalised reciprocal of its top 64 bits. Returns 0.
// @ref ?upton_munits@@3HA=00a7123c
// @ref ?upton_recipl@@3GA=00a71240
// @ref ?upton_reciprocal@@3PAKA=00a71244
// @ref ?upton_modulus@@3PAKA=00a71254
// @ref ?upton_reciph@@3GA=00a71354
// @ref ?upton_nbits@@3HA=00a71358
// @ref ?upton_mpdbuf@@3PAKA=00a7135c
// @ref ?upton_mshift@@3HA=00a71564
// @ref ?upton_dmi@@3PAKA=00a71568
#include "shared/mpmath.hpp"

// Upton modular-multiplication state (MPMath.cpp globals, .bss).
int upton_munits;                                // 16-bit units in the modulus
unsigned short upton_recipl;                     // low half of the reciprocal
digit upton_reciprocal[4];                       // reciprocal of the top modulus bits
digit upton_modulus[MAX_UNIT_PRECISION];         // the modulus
unsigned short upton_reciph = 0;                   // high half of the reciprocal
int upton_nbits;                                 // significant bits of the modulus
digit upton_mpdbuf[MAX_UNIT_PRECISION * 2 + 2];  // double-length product
int upton_mshift;                                // quotient-digit normalising shift
digit upton_dmi[4];                              // top 64 bits of the modulus

int __fastcall XMP_Prepare_Modulus(digit const *modulus, int precision)
{
    XMP_Move(upton_modulus, modulus, precision);
    upton_nbits = XMP_Count_Bits(upton_modulus, precision);
    upton_munits = (upton_nbits + 15) / 16;

    int prec = XMP_Significance(upton_modulus, precision);
    XMP_Move(upton_dmi, &upton_modulus[prec - 2], 2);
    upton_mshift = XMP_Count_Bits(upton_dmi, 2) - 32;
    XMP_Shift_Right_Bits(upton_dmi, upton_mshift, 2);
    XMP_Reciprocal(upton_reciprocal, upton_dmi, 2);
    XMP_Shift_Right_Bits(upton_reciprocal, 1, 2);
    upton_mshift = (upton_mshift + 15) % 16 + 1;
    XMP_Inc(upton_reciprocal, 2);
    if ((unsigned)XMP_Count_Bits(upton_reciprocal, 2) > 32) {
        XMP_Shift_Right_Bits(upton_reciprocal, 1, 2);
        upton_mshift--;
    }
    upton_recipl = ((unsigned short *)upton_reciprocal)[0];
    upton_reciph = ((unsigned short *)upton_reciprocal)[1];
    return 0;
}
