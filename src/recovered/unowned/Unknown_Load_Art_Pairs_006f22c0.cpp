// void Unknown_006F22C0() -- 0x006F22C0
// Loads the shell art pairs (shape and companion data) named at 0x007F86E8 and 0x007F86EC (hypothesis).
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f86e8@@3QBDB=007f86e8
// @ref ?unknown_name_7f86ec@@3QBDB=007f86ec
// @ref ?unknown_art_ac1130@@3PAXA=00ac1130
// @ref ?unknown_art_ac1134@@3PAXA=00ac1134
// @ref ?unknown_art_ac1138@@3PAXA=00ac1138
// @ref ?unknown_art_ac113c@@3PAXA=00ac113c
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);
extern char const * const unknown_name_7f86e8;
extern char const * const unknown_name_7f86ec;
extern void *unknown_art_ac1130;
extern void *unknown_art_ac1134;
extern void *unknown_art_ac1138;
extern void *unknown_art_ac113c;
void __fastcall Unknown_006F22C0()
{
    unknown_load_art_6f1fa0(unknown_name_7f86e8, &unknown_art_ac1130, &unknown_art_ac1134);
    unknown_load_art_6f1fa0(unknown_name_7f86ec, &unknown_art_ac1138, &unknown_art_ac113c);
}
