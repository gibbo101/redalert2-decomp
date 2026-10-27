// void Unknown_Free_Art_Sets_006F2510()
// Frees the three art pairs 0x006F24A0 loads (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1140@@3PAXA=00ac1140
// @ref ?unknown_art_ac1144@@3PAVUnknownArtData_006f2390@@A=00ac1144
// @ref ?unknown_art_ac1148@@3PAXA=00ac1148
// @ref ?unknown_art_ac114c@@3PAVUnknownArtData_006f2390@@A=00ac114c
// @ref ?unknown_art_ac1150@@3PAXA=00ac1150
// @ref ?unknown_art_ac1154@@3PAVUnknownArtData_006f2390@@A=00ac1154

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1140;
extern UnknownArtData_006f2390 *unknown_art_ac1144;
extern void *unknown_art_ac1148;
extern UnknownArtData_006f2390 *unknown_art_ac114c;
extern void *unknown_art_ac1150;
extern UnknownArtData_006f2390 *unknown_art_ac1154;

void __fastcall Unknown_Free_Art_Sets_006F2510()
{
    if (unknown_art_ac1140 != 0) {
        operator delete(unknown_art_ac1140);
        unknown_art_ac1140 = 0;
    }
    if (unknown_art_ac1144 != 0) {
        delete unknown_art_ac1144;
        unknown_art_ac1144 = 0;
    }
    if (unknown_art_ac1148 != 0) {
        operator delete(unknown_art_ac1148);
        unknown_art_ac1148 = 0;
    }
    if (unknown_art_ac114c != 0) {
        delete unknown_art_ac114c;
        unknown_art_ac114c = 0;
    }
    if (unknown_art_ac1150 != 0) {
        operator delete(unknown_art_ac1150);
        unknown_art_ac1150 = 0;
    }
    if (unknown_art_ac1154 != 0) {
        delete unknown_art_ac1154;
        unknown_art_ac1154 = 0;
    }
}
