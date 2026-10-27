// void Unknown_Free_Art_Buffers_006F2ED0() -- 0x006F2ED0
// Frees the four flagged buffers of the shell (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1228@@3_NA=00ac1228
// @ref ?unknown_flag_ac1229@@3_NA=00ac1229
// @ref ?unknown_flag_ac122a@@3_NA=00ac122a
// @ref ?unknown_flag_ac122b@@3_NA=00ac122b
// @ref ?unknown_art_ac1120@@3PAXA=00ac1120
// @ref ?unknown_art_ac1040@@3PAXA=00ac1040
// @ref ?unknown_art_ac10fc@@3PAXA=00ac10fc
// @ref ?unknown_art_ac1074@@3PAXA=00ac1074

extern bool unknown_flag_ac1228;
extern bool unknown_flag_ac1229;
extern bool unknown_flag_ac122a;
extern bool unknown_flag_ac122b;
extern void * unknown_art_ac1120;
extern void * unknown_art_ac1040;
extern void * unknown_art_ac10fc;
extern void * unknown_art_ac1074;

void __fastcall Unknown_Free_Art_Buffers_006F2ED0()
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
}

