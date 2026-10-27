// void Unknown_Free_Art_Buffers_006F22F0() -- 0x006F22F0
// Frees the four flagged buffers of the shell (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1224@@3_NA=00ac1224
// @ref ?unknown_flag_ac1225@@3_NA=00ac1225
// @ref ?unknown_flag_ac1226@@3_NA=00ac1226
// @ref ?unknown_flag_ac1227@@3_NA=00ac1227
// @ref ?unknown_art_ac1218@@3PAXA=00ac1218
// @ref ?unknown_art_ac121c@@3PAXA=00ac121c
// @ref ?unknown_art_ac1220@@3PAXA=00ac1220
// @ref ?unknown_art_ac10c0@@3PAXA=00ac10c0

extern bool unknown_flag_ac1224;
extern bool unknown_flag_ac1225;
extern bool unknown_flag_ac1226;
extern bool unknown_flag_ac1227;
extern void * unknown_art_ac1218;
extern void * unknown_art_ac121c;
extern void * unknown_art_ac1220;
extern void * unknown_art_ac10c0;

void __fastcall Unknown_Free_Art_Buffers_006F22F0()
{
    if (unknown_flag_ac1224) {
        operator delete(unknown_art_ac1218);
        unknown_flag_ac1224 = false;
    }
    unknown_art_ac1218 = 0;
    if (unknown_flag_ac1225) {
        operator delete(unknown_art_ac121c);
        unknown_flag_ac1225 = false;
    }
    unknown_art_ac121c = 0;
    if (unknown_flag_ac1226) {
        operator delete(unknown_art_ac1220);
        unknown_flag_ac1226 = false;
    }
    unknown_art_ac1220 = 0;
    if (unknown_flag_ac1227) {
        operator delete(unknown_art_ac10c0);
        unknown_flag_ac1227 = false;
    }
    unknown_art_ac10c0 = 0;
}

