// XMP_Mod_Mult_Clear(int precision) (0x005A9720)
// Wipes the modular-multiplication state.
#include "shared/mpmath.hpp"

void __fastcall XMP_Mod_Mult_Clear(int precision)
{
    XMP_Init(upton_modulus, 0, precision);
    upton_nbits = 0;
    XMP_Init(upton_mpdbuf, 0, precision);
    upton_mshift = 0;
    upton_recipl = 0;
    XMP_Init(upton_reciprocal, 0, 4);
    XMP_Init(upton_dmi, 0, 4);
    upton_reciph = 0;
    upton_munits = 0;
}
