// void Unknown_Free_Art_Buffers_006F2980() -- 0x006F2980
// Frees the three flagged art buffers (0x00AC110C, 0x00AC10F0, 0x00AC1108; each freed only when
// it was allocated) and clears their pointers: the body of 0x006F2750 without its loaded test.
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1214@@3_NA=00ac1214
// @ref ?unknown_flag_ac1215@@3_NA=00ac1215
// @ref ?unknown_flag_ac1216@@3_NA=00ac1216
// @ref ?unknown_art_ac110c@@3PAXA=00ac110c
// @ref ?unknown_art_ac10f0@@3PAXA=00ac10f0
// @ref ?unknown_art_ac1108@@3PAXA=00ac1108

extern bool unknown_flag_ac1214;
extern bool unknown_flag_ac1215;
extern bool unknown_flag_ac1216;
extern void *unknown_art_ac110c;
extern void *unknown_art_ac10f0;
extern void *unknown_art_ac1108;

void __fastcall Unknown_Free_Art_Buffers_006F2980()
{
    if (unknown_flag_ac1214) {
        operator delete(unknown_art_ac110c);
        unknown_flag_ac1214 = false;
    }
    unknown_art_ac110c = 0;
    if (unknown_flag_ac1215) {
        operator delete(unknown_art_ac10f0);
        unknown_flag_ac1215 = false;
    }
    unknown_art_ac10f0 = 0;
    if (unknown_flag_ac1216) {
        operator delete(unknown_art_ac1108);
        unknown_flag_ac1216 = false;
    }
    unknown_art_ac1108 = 0;
}
