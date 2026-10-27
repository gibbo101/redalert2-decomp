// void __fastcall unknown_load_art_7f8708(int alternate) -- 0x006F2960
// Purpose: loads one of two named art sets (the second when alternate is set) through 0x006F1FA0.
// Assumptions: 0x006F1FA0 (__fastcall) loads the named art into two
// outputs (a shape and its companion data; hypothesis); the name and
// output globals are unidentified.
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8708@@3QBDB=007f8708
// @ref ?unknown_art_ac1160@@3PAXA=00ac1160
// @ref ?unknown_art_ac1164@@3PAXA=00ac1164
// @ref ?unknown_name_7f870c@@3QBDB=007f870c

void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8708;
extern void *unknown_art_ac1160;
extern void *unknown_art_ac1164;
extern char const * const unknown_name_7f870c;

void __fastcall unknown_load_art_7f8708(int alternate)
{
    unknown_load_art_6f1fa0(alternate == 0 ? unknown_name_7f8708 : unknown_name_7f870c, &unknown_art_ac1160, &unknown_art_ac1164);
}
