// void __fastcall unknown_select_color(int which) -- 0x006F45A0
// Purpose: copies one of two 3-byte colors (0x00AC0FE8 for 0, 0x00AC10F4
// otherwise) into 0x00AC1028.
// Assumptions: the three colors are unidentified globals.
// @ref ?unknown_color_ac0fe8@@3UUnknownColor_006f45a0@@A=00ac0fe8
// @ref ?unknown_color_ac10f4@@3UUnknownColor_006f45a0@@A=00ac10f4
// @ref ?unknown_color_ac1028@@3UUnknownColor_006f45a0@@A=00ac1028

struct UnknownColor_006f45a0 {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};
extern UnknownColor_006f45a0 unknown_color_ac0fe8;
extern UnknownColor_006f45a0 unknown_color_ac10f4;
extern UnknownColor_006f45a0 unknown_color_ac1028;

void __fastcall unknown_select_color(int which)
{
    if (which == 0) {
        unknown_color_ac1028 = unknown_color_ac0fe8;
        return;
    }
    unknown_color_ac1028 = unknown_color_ac10f4;
}
