// void Unknown_6F4450() -- 0x006F44D0
// Releases the two art pairs 0x006F4C60 loads and the blocks 0x006F5400 frees (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_006F4B00@@YIXXZ=006f4b00
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8728@@3QBDB=007f8728
// @ref ?unknown_name_7f872c@@3QBDB=007f872c
// @ref ?Unknown_006F4C90@@YIXHH@Z=006f4c90
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_value_8523e4@@3HA=008523e4
// @ref ?Unknown_006F5150@@YIXXZ=006f5150
// @ref ?Unknown_006F5400@@YIXXZ=006f5400
// @ref ?unknown_flag_ac11b0@@3_NA=00ac11b0
// @ref ?unknown_art_ac11a0@@3PAXA=00ac11a0
// @ref ?unknown_art_ac11a4@@3PAVUnknownArtData_006f2390@@A=00ac11a4
// @ref ?unknown_art_ac11a8@@3PAXA=00ac11a8
// @ref ?unknown_art_ac11ac@@3PAVUnknownArtData_006f2390@@A=00ac11ac

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
void __fastcall Unknown_006F5150();
void __fastcall Unknown_006F4B00();
void __fastcall Unknown_006F4C90(int arg1, int arg2);
extern int unknown_value_8523e0;
extern int unknown_value_8523e4;
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8728;
extern char const * const unknown_name_7f872c;
void __fastcall Unknown_006F5400();
extern bool unknown_flag_ac11b0;
extern void *unknown_art_ac11a0;
extern UnknownArtData_006f2390 *unknown_art_ac11a4;
extern void *unknown_art_ac11a8;
extern UnknownArtData_006f2390 *unknown_art_ac11ac;

void __fastcall Unknown_6F4450()
{
    Unknown_006F5150();
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
    Unknown_006F5400();
    unknown_flag_ac11b0 = false;
    Unknown_006F4B00();
    unknown_load_art_6f1fa0(unknown_name_7f8728, &unknown_art_ac11a0, (void **)&unknown_art_ac11a4);
    unknown_load_art_6f1fa0(unknown_name_7f872c, &unknown_art_ac11a8, (void **)&unknown_art_ac11ac);
    Unknown_006F4C90(unknown_value_8523e0, unknown_value_8523e4);
    unknown_flag_ac11b0 = true;
}
