// void Unknown_Load_Art_Sets_006F20B0() -- 0x
// Loads the four flagged buffers and the two art pairs of the shell (hypothesis).
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0

void *__fastcall Unknown_00495270(char const *name, bool *allocated);
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
// @ref ?unknown_flag_ac1224@@3_NA=00ac1224
// @ref ?unknown_flag_ac1225@@3_NA=00ac1225
// @ref ?unknown_flag_ac1226@@3_NA=00ac1226
// @ref ?unknown_flag_ac1227@@3_NA=00ac1227
// @ref ?unknown_art_ac1218@@3PAXA=00ac1218
// @ref ?unknown_art_ac121c@@3PAXA=00ac121c
// @ref ?unknown_art_ac1220@@3PAXA=00ac1220
// @ref ?unknown_art_ac10c0@@3PAXA=00ac10c0
// @ref ?unknown_art_ac1130@@3PAXA=00ac1130
// @ref ?unknown_art_ac1134@@3PAXA=00ac1134
// @ref ?unknown_art_ac1138@@3PAXA=00ac1138
// @ref ?unknown_art_ac113c@@3PAXA=00ac113c
// @ref ?unknown_name_7f8740@@3QBDB=007f8740
// @ref ?unknown_name_7f8744@@3QBDB=007f8744
// @ref ?unknown_name_7f8748@@3QBDB=007f8748
// @ref ?unknown_name_7f874c@@3QBDB=007f874c
// @ref ?unknown_name_7f86e8@@3QBDB=007f86e8
// @ref ?unknown_name_7f86ec@@3QBDB=007f86ec

extern char const * const unknown_name_7f8740;
extern char const * const unknown_name_7f8744;
extern char const * const unknown_name_7f8748;
extern char const * const unknown_name_7f874c;
extern bool unknown_flag_ac1224;
extern bool unknown_flag_ac1225;
extern bool unknown_flag_ac1226;
extern bool unknown_flag_ac1227;
extern void *unknown_art_ac1218;
extern void *unknown_art_ac121c;
extern void *unknown_art_ac1220;
extern void *unknown_art_ac10c0;
extern char const * const unknown_name_7f86e8;
extern char const * const unknown_name_7f86ec;
extern void *unknown_art_ac1130;
extern void *unknown_art_ac1134;
extern void *unknown_art_ac1138;
extern void *unknown_art_ac113c;

void __fastcall Unknown_Load_Art_Sets_006F20B0()
{
    unknown_art_ac1218 = Unknown_00495270(unknown_name_7f8740, &unknown_flag_ac1224);
    unknown_art_ac121c = Unknown_00495270(unknown_name_7f8744, &unknown_flag_ac1225);
    unknown_art_ac1220 = Unknown_00495270(unknown_name_7f8748, &unknown_flag_ac1226);
    unknown_art_ac10c0 = Unknown_00495270(unknown_name_7f874c, &unknown_flag_ac1227);
    unknown_load_art_6f1fa0(unknown_name_7f86e8, &unknown_art_ac1130, (void **)&unknown_art_ac1134);
    unknown_load_art_6f1fa0(unknown_name_7f86ec, &unknown_art_ac1138, (void **)&unknown_art_ac113c);
}
