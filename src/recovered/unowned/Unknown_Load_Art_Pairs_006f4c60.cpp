// void Unknown_Load_Art_Pairs_006F4C60() (0x006F4C60)
// Loads the sidebar palettes SIDEBAR.PAL and UIBKGD.PAL with their drawers;
// 0x006F4620 expands it inline.
// @ref ?unknown_name_7f8728@@3QBDB=007f8728
// @ref ?unknown_name_7f872c@@3QBDB=007f872c
// @ref ?unknown_palette_ac11a0@@3PAVPaletteClass@@A=00ac11a0
// @ref ?unknown_drawer_ac11a4@@3PAVConvertClass@@A=00ac11a4
// @ref ?unknown_palette_ac11a8@@3PAVPaletteClass@@A=00ac11a8
// @ref ?unknown_drawer_ac11ac@@3PAVConvertClass@@A=00ac11ac
// @ref ?Unknown_Load_Palette_006F1FA0@@YIXPBDPAPAVPaletteClass@@PAPAVConvertClass@@@Z=006f1fa0
class PaletteClass;
class ConvertClass;

void __fastcall Unknown_Load_Palette_006F1FA0(char const *name, PaletteClass **palette, ConvertClass **drawer);
extern char const * const unknown_name_7f8728;   // SIDEBAR.PAL
extern char const * const unknown_name_7f872c;   // UIBKGD.PAL
extern PaletteClass *unknown_palette_ac11a0;
extern ConvertClass *unknown_drawer_ac11a4;
extern PaletteClass *unknown_palette_ac11a8;
extern ConvertClass *unknown_drawer_ac11ac;

void __fastcall Unknown_Load_Art_Pairs_006F4C60()
{
    Unknown_Load_Palette_006F1FA0(unknown_name_7f8728, &unknown_palette_ac11a0, &unknown_drawer_ac11a4);
    Unknown_Load_Palette_006F1FA0(unknown_name_7f872c, &unknown_palette_ac11a8, &unknown_drawer_ac11ac);
}
