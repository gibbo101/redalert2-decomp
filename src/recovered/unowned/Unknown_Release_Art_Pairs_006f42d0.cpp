// void Unknown_6F42D0() -- 0x006F42D0
// Releases the three art pairs 0x006F3E30 loads (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1184@@3PAXA=00ac1184
// @ref ?unknown_art_ac1188@@3PAVUnknownArtData_006f2390@@A=00ac1188
// @ref ?unknown_art_ac118c@@3PAXA=00ac118c
// @ref ?unknown_art_ac1190@@3PAVUnknownArtData_006f2390@@A=00ac1190
// @ref ?unknown_art_ac1194@@3PAXA=00ac1194
// @ref ?unknown_art_ac1198@@3PAVUnknownArtData_006f2390@@A=00ac1198

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1184;
extern UnknownArtData_006f2390 *unknown_art_ac1188;
extern void *unknown_art_ac118c;
extern UnknownArtData_006f2390 *unknown_art_ac1190;
extern void *unknown_art_ac1194;
extern UnknownArtData_006f2390 *unknown_art_ac1198;

void Unknown_6F42D0()
{
    if (unknown_art_ac1184 != 0) {
        operator delete(unknown_art_ac1184);
        unknown_art_ac1184 = 0;
    }
    if (unknown_art_ac1188 != 0) {
        delete unknown_art_ac1188;
        unknown_art_ac1188 = 0;
    }
    if (unknown_art_ac118c != 0) {
        operator delete(unknown_art_ac118c);
        unknown_art_ac118c = 0;
    }
    if (unknown_art_ac1190 != 0) {
        delete unknown_art_ac1190;
        unknown_art_ac1190 = 0;
    }
    if (unknown_art_ac1194 != 0) {
        operator delete(unknown_art_ac1194);
        unknown_art_ac1194 = 0;
    }
    if (unknown_art_ac1198 != 0) {
        delete unknown_art_ac1198;
        unknown_art_ac1198 = 0;
    }
}
