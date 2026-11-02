// void Unknown_Free_Art_Pair_006F29F0() -- 0x006F29F0
// Frees the art pair 0x00AC1160 / 0x00AC1164 (the second through its virtual destructor).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1160@@3PAXA=00ac1160
// @ref ?unknown_art_ac1164@@3PAVUnknownArtData_006f2390@@A=00ac1164

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1160;
extern UnknownArtData_006f2390 *unknown_art_ac1164;

void __fastcall Unknown_Free_Art_Pair_006F29F0()
{
    if (unknown_art_ac1160 != 0) {
        operator delete(unknown_art_ac1160);
        unknown_art_ac1160 = 0;
    }
    if (unknown_art_ac1164 != 0) {
        delete unknown_art_ac1164;
        unknown_art_ac1164 = 0;
    }
}
