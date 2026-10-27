// void Unknown_Load_Art_Pairs_006F3E30() -- 0x006F3E30
// Loads the three shell art pairs of the second set (hypothesis).
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f871c@@3QBDB=007f871c
// @ref ?unknown_name_7f8720@@3QBDB=007f8720
// @ref ?unknown_name_7f8724@@3QBDB=007f8724
// @ref ?unknown_art_ac1184@@3PAXA=00ac1184
// @ref ?unknown_art_ac1188@@3PAXA=00ac1188
// @ref ?unknown_art_ac118c@@3PAXA=00ac118c
// @ref ?unknown_art_ac1190@@3PAXA=00ac1190
// @ref ?unknown_art_ac1194@@3PAXA=00ac1194
// @ref ?unknown_art_ac1198@@3PAXA=00ac1198
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f871c;
extern char const * const unknown_name_7f8720;
extern char const * const unknown_name_7f8724;
extern void *unknown_art_ac1184;
extern void *unknown_art_ac1188;
extern void *unknown_art_ac118c;
extern void *unknown_art_ac1190;
extern void *unknown_art_ac1194;
extern void *unknown_art_ac1198;

void __fastcall Unknown_Load_Art_Pairs_006F3E30()
{
    unknown_load_art_6f1fa0(unknown_name_7f871c, &unknown_art_ac1184, &unknown_art_ac1188);
    unknown_load_art_6f1fa0(unknown_name_7f8720, &unknown_art_ac118c, &unknown_art_ac1190);
    unknown_load_art_6f1fa0(unknown_name_7f8724, &unknown_art_ac1194, &unknown_art_ac1198);
}
