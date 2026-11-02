// void Unknown_Free_Backdrop_006F2BD0() -- 0x006F2BD0
// Frees the backdrop shape 0x00AC1104 when it was allocated (flag 0x00AC1217) and clears it.
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1217@@3_NA=00ac1217
// @ref ?unknown_art_ac1104@@3PAXA=00ac1104

extern bool unknown_flag_ac1217;
extern void *unknown_art_ac1104;

void __fastcall Unknown_Free_Backdrop_006F2BD0()
{
    if (unknown_flag_ac1217) {
        operator delete(unknown_art_ac1104);
        unknown_flag_ac1217 = false;
    }
    unknown_art_ac1104 = 0;
}
