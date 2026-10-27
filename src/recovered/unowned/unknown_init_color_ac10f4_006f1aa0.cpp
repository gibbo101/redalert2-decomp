// void unknown_init_color_ac10f4() -- 0x006F1AA0
// Purpose: sets the three-byte colour at 0x00AC10F4 to (0xFF, 0xFF, 0); one of
// a run of colour initializers (0x006F1A40, 0x006F1A80, 0x006F1A60).
// Assumptions: the global is a red/green/blue byte triple.

struct UnknownColor_6f1aa0 {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};
extern UnknownColor_6f1aa0 unknown_color_ac10f4;
// @ref ?unknown_color_ac10f4@@3UUnknownColor_6f1aa0@@A=00ac10f4

void unknown_init_color_ac10f4()
{
    unknown_color_ac10f4.Red = 0xFF;
    unknown_color_ac10f4.Green = 0xFF;
    unknown_color_ac10f4.Blue = 0;
}
