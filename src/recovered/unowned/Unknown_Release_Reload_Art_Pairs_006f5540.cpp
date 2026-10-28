// void __fastcall Unknown_Release_Reload_Art_Pairs_006F5540() -- 0x006F5540
// Frees the two art pairs 0x006F4C60 loads and loads them again (hypothesis);
// the load calls of 0x006F4C60 are expanded inline.
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8728@@3QBDB=007f8728
// @ref ?unknown_name_7f872c@@3QBDB=007f872c
// @ref ?unknown_art_ac11a0@@3PAXA=00ac11a0
// @ref ?unknown_art_ac11a4@@3PAVUnknownArtData_006f2390@@A=00ac11a4
// @ref ?unknown_art_ac11a8@@3PAXA=00ac11a8
// @ref ?unknown_art_ac11ac@@3PAVUnknownArtData_006f2390@@A=00ac11ac
class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac11a0;
extern UnknownArtData_006f2390 *unknown_art_ac11a4;
extern void *unknown_art_ac11a8;
extern UnknownArtData_006f2390 *unknown_art_ac11ac;
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8728;
extern char const * const unknown_name_7f872c;

void __fastcall Unknown_Release_Reload_Art_Pairs_006F5540()
{
    if (unknown_art_ac11a0 != 0) {
        operator delete(unknown_art_ac11a0);
        unknown_art_ac11a0 = 0;
    }
    if (unknown_art_ac11a4 != 0) {
        delete unknown_art_ac11a4;
        unknown_art_ac11a4 = 0;
    }
    if (unknown_art_ac11a8 != 0) {
        operator delete(unknown_art_ac11a8);
        unknown_art_ac11a8 = 0;
    }
    if (unknown_art_ac11ac != 0) {
        delete unknown_art_ac11ac;
        unknown_art_ac11ac = 0;
    }
    unknown_load_art_6f1fa0(unknown_name_7f8728, &unknown_art_ac11a0, (void **)&unknown_art_ac11a4);
    unknown_load_art_6f1fa0(unknown_name_7f872c, &unknown_art_ac11a8, (void **)&unknown_art_ac11ac);
}
