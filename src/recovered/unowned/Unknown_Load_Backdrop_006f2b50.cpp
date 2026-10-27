// void __fastcall Unknown_006F2B50(int alternate) -- 0x006F2B50
// Loads the backdrop shape into 0x00AC1104: one of two names for the normal set (by
// whether the screen width at 0x008523E0 is 640) and one of two for the alternate set
// (hypothesis; 0x006F2A30 loads the same shape).
// @ref ?Unknown_00495270@@YIPAXPBDPA_N@Z=00495270
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_flag_ac1217@@3_NA=00ac1217
// @ref ?unknown_art_ac1104@@3PAXA=00ac1104
// @ref ?unknown_name_7f8780@@3QBDB=007f8780
// @ref ?unknown_name_7f8784@@3QBDB=007f8784
// @ref ?unknown_name_7f8788@@3QBDB=007f8788
// @ref ?unknown_name_7f878c@@3QBDB=007f878c

void *__fastcall Unknown_00495270(char const *name, bool *allocated);
extern int unknown_value_8523e0;
extern bool unknown_flag_ac1217;
extern void *unknown_art_ac1104;
extern char const * const unknown_name_7f8780;
extern char const * const unknown_name_7f8784;
extern char const * const unknown_name_7f8788;
extern char const * const unknown_name_7f878c;

void __fastcall Unknown_006F2B50(int alternate)
{
    if (alternate == 0) {
        if (unknown_value_8523e0 == 0x280) {
            unknown_art_ac1104 = Unknown_00495270(unknown_name_7f8780, &unknown_flag_ac1217);
        } else {
            unknown_art_ac1104 = Unknown_00495270(unknown_name_7f8784, &unknown_flag_ac1217);
        }
    } else {
        if (unknown_value_8523e0 == 0x280) {
            unknown_art_ac1104 = Unknown_00495270(unknown_name_7f8788, &unknown_flag_ac1217);
        } else {
            unknown_art_ac1104 = Unknown_00495270(unknown_name_7f878c, &unknown_flag_ac1217);
        }
    }
}
