// void Unknown_Load_MP_Loading_Palette_006F25C0() (0x006F25C0)
// Keeps the multiplayer loading-screen palette in step with the observer
// flag 0x00A72C68: frees MPLS.PAL when observing (state 1) or MPLSOBS.PAL when
// not (state 2), then loads the right one (state 0x00AC1248: 0 none, 1 MPLS,
// 2 MPLSOBS).
// @ref ?unknown_a72c68@@3HA=00a72c68
// @ref ?unknown_state_ac1248@@3HA=00ac1248
// @ref ?unknown_name_7f8700@@3QBDB=007f8700
// @ref ?unknown_name_7f8704@@3QBDB=007f8704
// @ref ?Unknown_Load_Palette_006F1FA0@@YIXPBDPAPAVPaletteClass@@PAPAVConvertClass@@@Z=006f1fa0
#include "shared/convert.hpp"

void __fastcall Unknown_Load_Palette_006F1FA0(char const *name, PaletteClass **palette, ConvertClass **drawer);
void __fastcall Unknown_Free_Art_Pair_006F26D0();
extern int unknown_a72c68;                        // observer (hypothesis)
extern int unknown_state_ac1248;
extern char const * const unknown_name_7f8700;    // MPLS.PAL
extern char const * const unknown_name_7f8704;    // MPLSOBS.PAL
extern PaletteClass *unknown_palette_ac1158;
extern ConvertClass *unknown_drawer_ac115c;

void __fastcall Unknown_Load_MP_Loading_Palette_006F25C0()
{
    if (unknown_state_ac1248 == 1 && unknown_a72c68 != 0) {
        Unknown_Free_Art_Pair_006F26D0();
    }
    if (unknown_state_ac1248 == 2 && unknown_a72c68 == 0) {
        Unknown_Free_Art_Pair_006F26D0();
    }
    if (unknown_drawer_ac115c == 0) {
        unknown_state_ac1248 = 0;
    }
    if (unknown_state_ac1248 == 0) {
        if (unknown_a72c68 != 0) {
            Unknown_Load_Palette_006F1FA0(unknown_name_7f8704, &unknown_palette_ac1158, &unknown_drawer_ac115c);
            unknown_state_ac1248 = 2;
        } else {
            Unknown_Load_Palette_006F1FA0(unknown_name_7f8700, &unknown_palette_ac1158, &unknown_drawer_ac115c);
            unknown_state_ac1248 = 1;
        }
    }
}
