// void Unknown_006F2B50(int alternate) (0x006F2B50)
// Loads the multiplayer score screen backdrop into 0x00AC1104: MPASCRNS/L for
// the normal set, MPSSCRNS/L for the alternate one, small when the screen is
// 640 wide (0x008523E0). 0x006F2A30 expands it inline.
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_flag_ac1217@@3_NA=00ac1217
// @ref ?unknown_shape_ac1104@@3PBXB=00ac1104
// @ref ?unknown_name_7f8780@@3QBDB=007f8780
// @ref ?unknown_name_7f8784@@3QBDB=007f8784
// @ref ?unknown_name_7f8788@@3QBDB=007f8788
// @ref ?unknown_name_7f878c@@3QBDB=007f878c
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270

void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);
extern int unknown_value_8523e0;                 // screen width
extern bool unknown_flag_ac1217;
extern void const *unknown_shape_ac1104;
extern char const * const unknown_name_7f8780;   // MPASCRNS.SHP
extern char const * const unknown_name_7f8784;   // MPASCRNL.SHP
extern char const * const unknown_name_7f8788;   // MPSSCRNS.SHP
extern char const * const unknown_name_7f878c;   // MPSSCRNL.SHP

void __fastcall Unknown_006F2B50(int alternate)
{
    if (alternate == 0) {
        if (unknown_value_8523e0 == 0x280) {
            unknown_shape_ac1104 = Unknown_Load_Shape_00495270(unknown_name_7f8780, unknown_flag_ac1217);
        } else {
            unknown_shape_ac1104 = Unknown_Load_Shape_00495270(unknown_name_7f8784, unknown_flag_ac1217);
        }
    } else {
        if (unknown_value_8523e0 == 0x280) {
            unknown_shape_ac1104 = Unknown_Load_Shape_00495270(unknown_name_7f8788, unknown_flag_ac1217);
        } else {
            unknown_shape_ac1104 = Unknown_Load_Shape_00495270(unknown_name_7f878c, unknown_flag_ac1217);
        }
    }
}
