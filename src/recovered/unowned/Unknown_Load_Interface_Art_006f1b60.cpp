// void Unknown_006F1B60() (0x006F1B60)
// Loads the interface art (hypothesis): four shapes by name into their slots,
// two blocks with their objects, and, once (flag 0x00AC119C), ten more shapes,
// three more blocks and the final 0x006F3E70 call with the two values at 0x008523E0.
// Anything loaded before is released by 0x006F5390 / 0x006F5540.
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?Unknown_006F1FA0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?Unknown_0051A2B0@@YIXXZ=0051a2b0
// @ref ?Unknown_006F3E70@@YIXHH@Z=006f3e70
// @ref ?unknown_flag_ac119c@@3_NA=00ac119c
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_value_8523e4@@3HA=008523e4
// @ref ?unknown_name_7f8740@@3PBDB=007f8740
// @ref ?unknown_flag_ac1224@@3_NA=00ac1224
// @ref ?unknown_art_ac1218@@3PAXA=00ac1218
// @ref ?unknown_name_7f8744@@3PBDB=007f8744
// @ref ?unknown_flag_ac1225@@3_NA=00ac1225
// @ref ?unknown_art_ac121c@@3PAXA=00ac121c
// @ref ?unknown_name_7f8748@@3PBDB=007f8748
// @ref ?unknown_flag_ac1226@@3_NA=00ac1226
// @ref ?unknown_art_ac1220@@3PAXA=00ac1220
// @ref ?unknown_name_7f874c@@3PBDB=007f874c
// @ref ?unknown_flag_ac1227@@3_NA=00ac1227
// @ref ?unknown_art_ac10c0@@3PAXA=00ac10c0
// @ref ?unknown_name_7f86e8@@3PBDB=007f86e8
// @ref ?unknown_block_ac1130@@3PAXA=00ac1130
// @ref ?unknown_object_ac1134@@3PAUUnknownOwnedObject@@A=00ac1134
// @ref ?unknown_name_7f86ec@@3PBDB=007f86ec
// @ref ?unknown_block_ac1138@@3PAXA=00ac1138
// @ref ?unknown_object_ac113c@@3PAUUnknownOwnedObject@@A=00ac113c
// @ref ?unknown_name_7f87b0@@3PBDB=007f87b0
// @ref ?unknown_flag_ac122c@@3_NA=00ac122c
// @ref ?unknown_art_ac10b8@@3PAXA=00ac10b8
// @ref ?unknown_name_7f87b4@@3PBDB=007f87b4
// @ref ?unknown_flag_ac122d@@3_NA=00ac122d
// @ref ?unknown_art_ac0fec@@3PAXA=00ac0fec
// @ref ?unknown_name_7f87b8@@3PBDB=007f87b8
// @ref ?unknown_flag_ac122e@@3_NA=00ac122e
// @ref ?unknown_art_ac10b4@@3PAXA=00ac10b4
// @ref ?unknown_name_7f87bc@@3PBDB=007f87bc
// @ref ?unknown_flag_ac122f@@3_NA=00ac122f
// @ref ?unknown_art_ac1128@@3PAXA=00ac1128
// @ref ?unknown_name_7f87c0@@3PBDB=007f87c0
// @ref ?unknown_flag_ac1230@@3_NA=00ac1230
// @ref ?unknown_art_ac1010@@3PAXA=00ac1010
// @ref ?unknown_name_7f87c4@@3PBDB=007f87c4
// @ref ?unknown_flag_ac1231@@3_NA=00ac1231
// @ref ?unknown_art_ac10e8@@3PAXA=00ac10e8
// @ref ?unknown_name_7f87c8@@3PBDB=007f87c8
// @ref ?unknown_flag_ac1232@@3_NA=00ac1232
// @ref ?unknown_art_ac107c@@3PAXA=00ac107c
// @ref ?unknown_name_7f87cc@@3PBDB=007f87cc
// @ref ?unknown_flag_ac1233@@3_NA=00ac1233
// @ref ?unknown_art_ac1044@@3PAXA=00ac1044
// @ref ?unknown_name_7f87d0@@3PBDB=007f87d0
// @ref ?unknown_flag_ac1234@@3_NA=00ac1234
// @ref ?unknown_art_ac10d8@@3PAXA=00ac10d8
// @ref ?unknown_name_7f87d4@@3PBDB=007f87d4
// @ref ?unknown_flag_ac1235@@3_NA=00ac1235
// @ref ?unknown_art_ac1060@@3PAXA=00ac1060
// @ref ?unknown_name_7f871c@@3PBDB=007f871c
// @ref ?unknown_block_ac1184@@3PAXA=00ac1184
// @ref ?unknown_object_ac1188@@3PAUUnknownOwnedObject@@A=00ac1188
// @ref ?unknown_name_7f8720@@3PBDB=007f8720
// @ref ?unknown_block_ac118c@@3PAXA=00ac118c
// @ref ?unknown_object_ac1190@@3PAUUnknownOwnedObject@@A=00ac1190
// @ref ?unknown_name_7f8724@@3PBDB=007f8724
// @ref ?unknown_block_ac1194@@3PAXA=00ac1194
// @ref ?unknown_object_ac1198@@3PAUUnknownOwnedObject@@A=00ac1198

struct UnknownOwnedObject {
    virtual ~UnknownOwnedObject();
};
void *__fastcall Unknown_00495270(char const *name, bool *found);
void __fastcall Unknown_006F1FA0(char const *name, void **shape, void **data);   // 0x006F1FA0
void __fastcall Unknown_0051A2B0();
void __fastcall Unknown_006F3E70(int arg1, int arg2);
extern bool unknown_flag_ac119c;
extern int unknown_value_8523e0;
extern int unknown_value_8523e4;
extern UnknownOwnedObject *unknown_object_ac1134;
extern UnknownOwnedObject *unknown_object_ac113c;
extern UnknownOwnedObject *unknown_object_ac1188;
extern UnknownOwnedObject *unknown_object_ac1190;
extern UnknownOwnedObject *unknown_object_ac1198;
extern bool unknown_flag_ac1224;
extern bool unknown_flag_ac1225;
extern bool unknown_flag_ac1226;
extern bool unknown_flag_ac1227;
extern bool unknown_flag_ac122c;
extern bool unknown_flag_ac122d;
extern bool unknown_flag_ac122e;
extern bool unknown_flag_ac122f;
extern bool unknown_flag_ac1230;
extern bool unknown_flag_ac1231;
extern bool unknown_flag_ac1232;
extern bool unknown_flag_ac1233;
extern bool unknown_flag_ac1234;
extern bool unknown_flag_ac1235;
extern char const *unknown_name_7f86e8;
extern char const *unknown_name_7f86ec;
extern char const *unknown_name_7f871c;
extern char const *unknown_name_7f8720;
extern char const *unknown_name_7f8724;
extern char const *unknown_name_7f8740;
extern char const *unknown_name_7f8744;
extern char const *unknown_name_7f8748;
extern char const *unknown_name_7f874c;
extern char const *unknown_name_7f87b0;
extern char const *unknown_name_7f87b4;
extern char const *unknown_name_7f87b8;
extern char const *unknown_name_7f87bc;
extern char const *unknown_name_7f87c0;
extern char const *unknown_name_7f87c4;
extern char const *unknown_name_7f87c8;
extern char const *unknown_name_7f87cc;
extern char const *unknown_name_7f87d0;
extern char const *unknown_name_7f87d4;
extern void *unknown_art_ac0fec;
extern void *unknown_art_ac1010;
extern void *unknown_art_ac1044;
extern void *unknown_art_ac1060;
extern void *unknown_art_ac107c;
extern void *unknown_art_ac10b4;
extern void *unknown_art_ac10b8;
extern void *unknown_art_ac10c0;
extern void *unknown_art_ac10d8;
extern void *unknown_art_ac10e8;
extern void *unknown_art_ac1128;
extern void *unknown_art_ac1218;
extern void *unknown_art_ac121c;
extern void *unknown_art_ac1220;
extern void *unknown_block_ac1130;
extern void *unknown_block_ac1138;
extern void *unknown_block_ac1184;
extern void *unknown_block_ac118c;
extern void *unknown_block_ac1194;

void __fastcall Unknown_006F1B60()
{
    unknown_art_ac1218 = Unknown_00495270(unknown_name_7f8740, &unknown_flag_ac1224);
    unknown_art_ac121c = Unknown_00495270(unknown_name_7f8744, &unknown_flag_ac1225);
    unknown_art_ac1220 = Unknown_00495270(unknown_name_7f8748, &unknown_flag_ac1226);
    unknown_art_ac10c0 = Unknown_00495270(unknown_name_7f874c, &unknown_flag_ac1227);
    Unknown_006F1FA0(unknown_name_7f86e8, &unknown_block_ac1130, (void **)&unknown_object_ac1134);
    Unknown_006F1FA0(unknown_name_7f86ec, &unknown_block_ac1138, (void **)&unknown_object_ac113c);
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
        Unknown_006F1FA0(unknown_name_7f871c, &unknown_block_ac1184, (void **)&unknown_object_ac1188);
        Unknown_006F1FA0(unknown_name_7f8720, &unknown_block_ac118c, (void **)&unknown_object_ac1190);
        Unknown_006F1FA0(unknown_name_7f8724, &unknown_block_ac1194, (void **)&unknown_object_ac1198);
        Unknown_006F3E70(unknown_value_8523e0, unknown_value_8523e4);
        unknown_flag_ac119c = true;
    }
}
