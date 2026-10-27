// void Unknown_Free_Art_Pair_006F26D0()
// Frees the art pair at 0x00AC1158/0x00AC115C (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1158@@3PAXA=00ac1158
// @ref ?unknown_art_ac115c@@3PAVUnknownArtData_006f2390@@A=00ac115c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1158;
extern UnknownArtData_006f2390 *unknown_art_ac115c;

void __fastcall Unknown_Free_Art_Pair_006F26D0()
{
    if (unknown_art_ac1158 != 0) {
        operator delete(unknown_art_ac1158);
        unknown_art_ac1158 = 0;
    }
    if (unknown_art_ac115c != 0) {
        delete unknown_art_ac115c;
        unknown_art_ac115c = 0;
    }
}
