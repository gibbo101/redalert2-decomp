// void Unknown_006F4160() -- 0x006F4160
// Frees the ten flagged buffers 0x006F2FB0 loads (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac122c@@3_NA=00ac122c
// @ref ?unknown_art_ac10b8@@3PAXA=00ac10b8
// @ref ?unknown_flag_ac122d@@3_NA=00ac122d
// @ref ?unknown_art_ac0fec@@3PAXA=00ac0fec
// @ref ?unknown_flag_ac122e@@3_NA=00ac122e
// @ref ?unknown_art_ac10b4@@3PAXA=00ac10b4
// @ref ?unknown_flag_ac122f@@3_NA=00ac122f
// @ref ?unknown_art_ac1128@@3PAXA=00ac1128
// @ref ?unknown_flag_ac1230@@3_NA=00ac1230
// @ref ?unknown_art_ac1010@@3PAXA=00ac1010
// @ref ?unknown_flag_ac1231@@3_NA=00ac1231
// @ref ?unknown_art_ac10e8@@3PAXA=00ac10e8
// @ref ?unknown_flag_ac1232@@3_NA=00ac1232
// @ref ?unknown_art_ac107c@@3PAXA=00ac107c
// @ref ?unknown_flag_ac1233@@3_NA=00ac1233
// @ref ?unknown_art_ac1044@@3PAXA=00ac1044
// @ref ?unknown_flag_ac1234@@3_NA=00ac1234
// @ref ?unknown_art_ac10d8@@3PAXA=00ac10d8
// @ref ?unknown_flag_ac1235@@3_NA=00ac1235
// @ref ?unknown_art_ac1060@@3PAXA=00ac1060

extern bool unknown_flag_ac122c;
extern void *unknown_art_ac10b8;
extern bool unknown_flag_ac122d;
extern void *unknown_art_ac0fec;
extern bool unknown_flag_ac122e;
extern void *unknown_art_ac10b4;
extern bool unknown_flag_ac122f;
extern void *unknown_art_ac1128;
extern bool unknown_flag_ac1230;
extern void *unknown_art_ac1010;
extern bool unknown_flag_ac1231;
extern void *unknown_art_ac10e8;
extern bool unknown_flag_ac1232;
extern void *unknown_art_ac107c;
extern bool unknown_flag_ac1233;
extern void *unknown_art_ac1044;
extern bool unknown_flag_ac1234;
extern void *unknown_art_ac10d8;
extern bool unknown_flag_ac1235;
extern void *unknown_art_ac1060;

void __fastcall Unknown_006F4160()
{
    if (unknown_flag_ac122c) {
        operator delete(unknown_art_ac10b8);
        unknown_flag_ac122c = false;
    }
    unknown_art_ac10b8 = 0;
    if (unknown_flag_ac122d) {
        operator delete(unknown_art_ac0fec);
        unknown_flag_ac122d = false;
    }
    unknown_art_ac0fec = 0;
    if (unknown_flag_ac122e) {
        operator delete(unknown_art_ac10b4);
        unknown_flag_ac122e = false;
    }
    unknown_art_ac10b4 = 0;
    if (unknown_flag_ac122f) {
        operator delete(unknown_art_ac1128);
        unknown_flag_ac122f = false;
    }
    unknown_art_ac1128 = 0;
    if (unknown_flag_ac1230) {
        operator delete(unknown_art_ac1010);
        unknown_flag_ac1230 = false;
    }
    unknown_art_ac1010 = 0;
    if (unknown_flag_ac1231) {
        operator delete(unknown_art_ac10e8);
        unknown_flag_ac1231 = false;
    }
    unknown_art_ac10e8 = 0;
    if (unknown_flag_ac1232) {
        operator delete(unknown_art_ac107c);
        unknown_flag_ac1232 = false;
    }
    unknown_art_ac107c = 0;
    if (unknown_flag_ac1233) {
        operator delete(unknown_art_ac1044);
        unknown_flag_ac1233 = false;
    }
    unknown_art_ac1044 = 0;
    if (unknown_flag_ac1234) {
        operator delete(unknown_art_ac10d8);
        unknown_flag_ac1234 = false;
    }
    unknown_art_ac10d8 = 0;
    if (unknown_flag_ac1235) {
        operator delete(unknown_art_ac1060);
        unknown_flag_ac1235 = false;
    }
    unknown_art_ac1060 = 0;
}
