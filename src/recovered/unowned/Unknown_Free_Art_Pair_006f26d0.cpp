// void Unknown_Free_Art_Pair_006F26D0() (0x006F26D0)
// Frees the multiplayer loading-screen palette 0x00AC1158 and its drawer
// 0x00AC115C (MPLS.PAL or MPLSOBS.PAL, loaded by 0x006F25C0).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_palette_ac1158@@3PAVPaletteClass@@A=00ac1158
// @ref ?unknown_drawer_ac115c@@3PAVConvertClass@@A=00ac115c
#include "shared/convert.hpp"

extern PaletteClass *unknown_palette_ac1158;
extern ConvertClass *unknown_drawer_ac115c;

void __fastcall Unknown_Free_Art_Pair_006F26D0()
{
    if (unknown_palette_ac1158 != 0) {
        delete unknown_palette_ac1158;
        unknown_palette_ac1158 = 0;
    }
    if (unknown_drawer_ac115c != 0) {
        delete unknown_drawer_ac115c;
        unknown_drawer_ac115c = 0;
    }
}
