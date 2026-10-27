// void unknown_load_art_7f8718() -- 0x006F2EB0
// Purpose: loads 1 named art set through 0x006F1FA0.
// Assumptions: 0x006F1FA0 (__fastcall) loads the named art into two
// outputs (a shape and its companion data; hypothesis); the name and
// output globals are unidentified.
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8718@@3QBDB=007f8718
// @ref ?unknown_art_ac1178@@3PAXA=00ac1178
// @ref ?unknown_art_ac117c@@3PAXA=00ac117c

void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8718;
extern void *unknown_art_ac1178;
extern void *unknown_art_ac117c;

void unknown_load_art_7f8718()
{
    unknown_load_art_6f1fa0(unknown_name_7f8718, &unknown_art_ac1178, &unknown_art_ac117c);
}
