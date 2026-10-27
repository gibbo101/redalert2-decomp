// void __fastcall unknown_load_art_7f8710(int alternate) -- 0x006F2BB0
// Purpose: loads one of two named art sets (the second when alternate is set) through 0x006F1FA0.
// Assumptions: 0x006F1FA0 (__fastcall) loads the named art into two
// outputs (a shape and its companion data; hypothesis); the name and
// output globals are unidentified.
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8710@@3QBDB=007f8710
// @ref ?unknown_art_ac116c@@3PAXA=00ac116c
// @ref ?unknown_art_ac1170@@3PAXA=00ac1170
// @ref ?unknown_name_7f8714@@3QBDB=007f8714

void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8710;
extern void *unknown_art_ac116c;
extern void *unknown_art_ac1170;
extern char const * const unknown_name_7f8714;

void __fastcall unknown_load_art_7f8710(int alternate)
{
    unknown_load_art_6f1fa0(alternate == 0 ? unknown_name_7f8710 : unknown_name_7f8714, &unknown_art_ac116c, &unknown_art_ac1170);
}
