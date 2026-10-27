// void Unknown_6F4450() -- 0x006F4450
// Releases the two art pairs 0x006F4C60 loads and the blocks 0x006F5400 frees (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
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
}
