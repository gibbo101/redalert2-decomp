// void Unknown_006F2C40() -- 0x006F2C40
// Loads four shapes into 0x00AC1120, 0x00AC1040, 0x00AC10FC and 0x00AC1074, named for the screen
// width (640 or not), recording in the flags at 0x00AC1228 whether each was allocated and the art pair at 0x00AC1178 (hypothesis).
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?unknown_name_7f8718@@3QBDB=007f8718
// @ref ?unknown_art_ac1178@@3PAXA=00ac1178
// @ref ?unknown_art_ac117c@@3PAXA=00ac117c
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_name_7f8790@@3QBDB=007f8790
// @ref ?unknown_name_7f8798@@3QBDB=007f8798
// @ref ?unknown_name_7f87a0@@3QBDB=007f87a0
// @ref ?unknown_name_7f87a8@@3QBDB=007f87a8
// @ref ?unknown_name_7f8794@@3QBDB=007f8794
// @ref ?unknown_name_7f879c@@3QBDB=007f879c
// @ref ?unknown_name_7f87a4@@3QBDB=007f87a4
// @ref ?unknown_name_7f87ac@@3QBDB=007f87ac
// @ref ?unknown_flag_ac1228@@3_NA=00ac1228
// @ref ?unknown_flag_ac1229@@3_NA=00ac1229
// @ref ?unknown_flag_ac122a@@3_NA=00ac122a
// @ref ?unknown_flag_ac122b@@3_NA=00ac122b
// @ref ?unknown_art_ac1120@@3PAXA=00ac1120
// @ref ?unknown_art_ac1040@@3PAXA=00ac1040
// @ref ?unknown_art_ac10fc@@3PAXA=00ac10fc
// @ref ?unknown_art_ac1074@@3PAXA=00ac1074

void *__fastcall Unknown_00495270(char const *name, bool *allocated);
extern int unknown_value_8523e0;
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
extern char const * const unknown_name_7f8718;
extern void *unknown_art_ac1178;
extern void *unknown_art_ac117c;
extern char const * const unknown_name_7f8790;
extern char const * const unknown_name_7f8798;
extern char const * const unknown_name_7f87a0;
extern char const * const unknown_name_7f87a8;
extern char const * const unknown_name_7f8794;
extern char const * const unknown_name_7f879c;
extern char const * const unknown_name_7f87a4;
extern char const * const unknown_name_7f87ac;
extern bool unknown_flag_ac1228;
extern bool unknown_flag_ac1229;
extern bool unknown_flag_ac122a;
extern bool unknown_flag_ac122b;
extern void *unknown_art_ac1120;
extern void *unknown_art_ac1040;
extern void *unknown_art_ac10fc;
extern void *unknown_art_ac1074;

void __fastcall Unknown_006F2C40()
{
    if (unknown_value_8523e0 == 0x280) {
        unknown_art_ac1120 = Unknown_00495270(unknown_name_7f8790, &unknown_flag_ac1228);
        unknown_art_ac1040 = Unknown_00495270(unknown_name_7f8798, &unknown_flag_ac1229);
        unknown_art_ac10fc = Unknown_00495270(unknown_name_7f87a0, &unknown_flag_ac122a);
        unknown_art_ac1074 = Unknown_00495270(unknown_name_7f87a8, &unknown_flag_ac122b);
    } else {
        unknown_art_ac1120 = Unknown_00495270(unknown_name_7f8794, &unknown_flag_ac1228);
        unknown_art_ac1040 = Unknown_00495270(unknown_name_7f879c, &unknown_flag_ac1229);
        unknown_art_ac10fc = Unknown_00495270(unknown_name_7f87a4, &unknown_flag_ac122a);
        unknown_art_ac1074 = Unknown_00495270(unknown_name_7f87ac, &unknown_flag_ac122b);
    }
    unknown_load_art_6f1fa0(unknown_name_7f8718, &unknown_art_ac1178, (void **)&unknown_art_ac117c);
}
