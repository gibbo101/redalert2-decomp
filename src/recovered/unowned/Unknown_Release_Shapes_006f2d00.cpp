// void Unknown_006F2D00() -- 0x006F2D00
// Releases the four shapes 0x006F2C40 / 0x006F2DF0 load (each freed only when its flag at
// 0x00AC1228 says it was allocated) and the art pair at 0x00AC1178 / 0x00AC117C (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1228@@3_NA=00ac1228
// @ref ?unknown_flag_ac1229@@3_NA=00ac1229
// @ref ?unknown_flag_ac122a@@3_NA=00ac122a
// @ref ?unknown_flag_ac122b@@3_NA=00ac122b
// @ref ?unknown_art_ac1120@@3PAXA=00ac1120
// @ref ?unknown_art_ac1040@@3PAXA=00ac1040
// @ref ?unknown_art_ac10fc@@3PAXA=00ac10fc
// @ref ?unknown_art_ac1074@@3PAXA=00ac1074
// @ref ?unknown_art_ac1178@@3PAXA=00ac1178
// @ref ?unknown_art_ac117c@@3PAVUnknownArtData_006f2390@@A=00ac117c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern bool unknown_flag_ac1228;
extern bool unknown_flag_ac1229;
extern bool unknown_flag_ac122a;
extern bool unknown_flag_ac122b;
extern void *unknown_art_ac1120;
extern void *unknown_art_ac1040;
extern void *unknown_art_ac10fc;
extern void *unknown_art_ac1074;
extern void *unknown_art_ac1178;
extern UnknownArtData_006f2390 *unknown_art_ac117c;

void __fastcall Unknown_006F2D00()
{
    if (unknown_flag_ac1228) {
        operator delete(unknown_art_ac1120);
        unknown_flag_ac1228 = false;
    }
    unknown_art_ac1120 = 0;
    if (unknown_flag_ac1229) {
        operator delete(unknown_art_ac1040);
        unknown_flag_ac1229 = false;
    }
    unknown_art_ac1040 = 0;
    if (unknown_flag_ac122a) {
        operator delete(unknown_art_ac10fc);
        unknown_flag_ac122a = false;
    }
    unknown_art_ac10fc = 0;
    if (unknown_flag_ac122b) {
        operator delete(unknown_art_ac1074);
        unknown_flag_ac122b = false;
    }
    unknown_art_ac1074 = 0;
    if (unknown_art_ac1178 != 0) {
        operator delete(unknown_art_ac1178);
        unknown_art_ac1178 = 0;
    }
    if (unknown_art_ac117c != 0) {
        delete unknown_art_ac117c;
        unknown_art_ac117c = 0;
    }
}
