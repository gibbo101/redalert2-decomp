// void Unknown_Load_Art_Pairs_006F4C60() -- 0x006F4C60
// Loads the two art pairs 0x006F4450 releases (hypothesis).
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8728@@3QBDB=007f8728
// @ref ?unknown_name_7f872c@@3QBDB=007f872c
// @ref ?unknown_art_ac11a0@@3PAXA=00ac11a0
// @ref ?unknown_art_ac11a4@@3PAXA=00ac11a4
// @ref ?unknown_art_ac11a8@@3PAXA=00ac11a8
// @ref ?unknown_art_ac11ac@@3PAXA=00ac11ac
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8728;
extern char const * const unknown_name_7f872c;
extern void *unknown_art_ac11a0;
extern void *unknown_art_ac11a4;
extern void *unknown_art_ac11a8;
extern void *unknown_art_ac11ac;

void __fastcall Unknown_Load_Art_Pairs_006F4C60()
{
    unknown_load_art_6f1fa0(unknown_name_7f8728, &unknown_art_ac11a0, &unknown_art_ac11a4);
    unknown_load_art_6f1fa0(unknown_name_7f872c, &unknown_art_ac11a8, &unknown_art_ac11ac);
}
