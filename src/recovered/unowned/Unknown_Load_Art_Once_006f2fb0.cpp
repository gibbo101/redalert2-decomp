// void Unknown_006F2FB0() -- 0x006F2FB0
// Once (flag 0x00AC119C): loads ten shapes, three art pairs and runs 0x006F3E70 with the two
// values at 0x008523E0 (hypothesis).
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?Unknown_0051A2B0@@YIXXZ=0051a2b0
// @ref ?Unknown_006F3E70@@YIXHH@Z=006f3e70
// @ref ?unknown_flag_ac119c@@3_NA=00ac119c
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_value_8523e4@@3HA=008523e4
// @ref ?unknown_name_7f87b0@@3QBDB=007f87b0
// @ref ?unknown_flag_ac122c@@3_NA=00ac122c
// @ref ?unknown_art_ac10b8@@3PAXA=00ac10b8
// @ref ?unknown_name_7f87b4@@3QBDB=007f87b4
// @ref ?unknown_flag_ac122d@@3_NA=00ac122d
// @ref ?unknown_art_ac0fec@@3PAXA=00ac0fec
// @ref ?unknown_name_7f87b8@@3QBDB=007f87b8
// @ref ?unknown_flag_ac122e@@3_NA=00ac122e
// @ref ?unknown_art_ac10b4@@3PAXA=00ac10b4
// @ref ?unknown_name_7f87bc@@3QBDB=007f87bc
// @ref ?unknown_flag_ac122f@@3_NA=00ac122f
// @ref ?unknown_art_ac1128@@3PAXA=00ac1128
// @ref ?unknown_name_7f87c0@@3QBDB=007f87c0
// @ref ?unknown_flag_ac1230@@3_NA=00ac1230
// @ref ?unknown_art_ac1010@@3PAXA=00ac1010
// @ref ?unknown_name_7f87c4@@3QBDB=007f87c4
// @ref ?unknown_flag_ac1231@@3_NA=00ac1231
// @ref ?unknown_art_ac10e8@@3PAXA=00ac10e8
// @ref ?unknown_name_7f87c8@@3QBDB=007f87c8
// @ref ?unknown_flag_ac1232@@3_NA=00ac1232
// @ref ?unknown_art_ac107c@@3PAXA=00ac107c
// @ref ?unknown_name_7f87cc@@3QBDB=007f87cc
// @ref ?unknown_flag_ac1233@@3_NA=00ac1233
// @ref ?unknown_art_ac1044@@3PAXA=00ac1044
// @ref ?unknown_name_7f87d0@@3QBDB=007f87d0
// @ref ?unknown_flag_ac1234@@3_NA=00ac1234
// @ref ?unknown_art_ac10d8@@3PAXA=00ac10d8
// @ref ?unknown_name_7f87d4@@3QBDB=007f87d4
// @ref ?unknown_flag_ac1235@@3_NA=00ac1235
// @ref ?unknown_art_ac1060@@3PAXA=00ac1060
// @ref ?unknown_name_7f871c@@3QBDB=007f871c
// @ref ?unknown_art_ac1184@@3PAXA=00ac1184
// @ref ?unknown_art_ac1188@@3PAXA=00ac1188
// @ref ?unknown_name_7f8720@@3QBDB=007f8720
// @ref ?unknown_art_ac118c@@3PAXA=00ac118c
// @ref ?unknown_art_ac1190@@3PAXA=00ac1190
// @ref ?unknown_name_7f8724@@3QBDB=007f8724
// @ref ?unknown_art_ac1194@@3PAXA=00ac1194
// @ref ?unknown_art_ac1198@@3PAXA=00ac1198

void *__fastcall Unknown_00495270(char const *name, bool *allocated);
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
void __fastcall Unknown_0051A2B0();
void __fastcall Unknown_006F3E70(int arg1, int arg2);
extern bool unknown_flag_ac119c;
extern int unknown_value_8523e0;
extern int unknown_value_8523e4;
extern char const * const unknown_name_7f87b0;
extern bool unknown_flag_ac122c;
extern void *unknown_art_ac10b8;
extern char const * const unknown_name_7f87b4;
extern bool unknown_flag_ac122d;
extern void *unknown_art_ac0fec;
extern char const * const unknown_name_7f87b8;
extern bool unknown_flag_ac122e;
extern void *unknown_art_ac10b4;
extern char const * const unknown_name_7f87bc;
extern bool unknown_flag_ac122f;
extern void *unknown_art_ac1128;
extern char const * const unknown_name_7f87c0;
extern bool unknown_flag_ac1230;
extern void *unknown_art_ac1010;
extern char const * const unknown_name_7f87c4;
extern bool unknown_flag_ac1231;
extern void *unknown_art_ac10e8;
extern char const * const unknown_name_7f87c8;
extern bool unknown_flag_ac1232;
extern void *unknown_art_ac107c;
extern char const * const unknown_name_7f87cc;
extern bool unknown_flag_ac1233;
extern void *unknown_art_ac1044;
extern char const * const unknown_name_7f87d0;
extern bool unknown_flag_ac1234;
extern void *unknown_art_ac10d8;
extern char const * const unknown_name_7f87d4;
extern bool unknown_flag_ac1235;
extern void *unknown_art_ac1060;
extern char const * const unknown_name_7f871c;
extern void *unknown_art_ac1184;
extern void *unknown_art_ac1188;
extern char const * const unknown_name_7f8720;
extern void *unknown_art_ac118c;
extern void *unknown_art_ac1190;
extern char const * const unknown_name_7f8724;
extern void *unknown_art_ac1194;
extern void *unknown_art_ac1198;

void __fastcall Unknown_006F2FB0()
{
    if (!unknown_flag_ac119c) {
        Unknown_0051A2B0();
        unknown_art_ac10b8 = Unknown_00495270(unknown_name_7f87b0, &unknown_flag_ac122c);
        unknown_art_ac0fec = Unknown_00495270(unknown_name_7f87b4, &unknown_flag_ac122d);
        unknown_art_ac10b4 = Unknown_00495270(unknown_name_7f87b8, &unknown_flag_ac122e);
        unknown_art_ac1128 = Unknown_00495270(unknown_name_7f87bc, &unknown_flag_ac122f);
        unknown_art_ac1010 = Unknown_00495270(unknown_name_7f87c0, &unknown_flag_ac1230);
        unknown_art_ac10e8 = Unknown_00495270(unknown_name_7f87c4, &unknown_flag_ac1231);
        unknown_art_ac107c = Unknown_00495270(unknown_name_7f87c8, &unknown_flag_ac1232);
        unknown_art_ac1044 = Unknown_00495270(unknown_name_7f87cc, &unknown_flag_ac1233);
        unknown_art_ac10d8 = Unknown_00495270(unknown_name_7f87d0, &unknown_flag_ac1234);
        unknown_art_ac1060 = Unknown_00495270(unknown_name_7f87d4, &unknown_flag_ac1235);
        unknown_load_art_6f1fa0(unknown_name_7f871c, &unknown_art_ac1184, (void **)&unknown_art_ac1188);
        unknown_load_art_6f1fa0(unknown_name_7f8720, &unknown_art_ac118c, (void **)&unknown_art_ac1190);
        unknown_load_art_6f1fa0(unknown_name_7f8724, &unknown_art_ac1194, (void **)&unknown_art_ac1198);
        Unknown_006F3E70(unknown_value_8523e0, unknown_value_8523e4);
        unknown_flag_ac119c = true;
    }
}
