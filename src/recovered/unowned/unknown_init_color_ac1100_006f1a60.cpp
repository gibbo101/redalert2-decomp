// void unknown_init_color_ac1100() -- 0x006F1A60
// Purpose: sets the three-byte colour at 0x00AC1100 to (0x48, 0, 0); one of
// a run of colour initializers (0x006F1A40, 0x006F1A80, 0x006F1AA0).
// Assumptions: the global is a red/green/blue byte triple.

struct UnknownColor_6f1a60 {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};
extern UnknownColor_6f1a60 unknown_color_ac1100;
// @ref ?unknown_color_ac1100@@3UUnknownColor_6f1a60@@A=00ac1100

void unknown_init_color_ac1100()
{
    unknown_color_ac1100.Red = 0x48;
    unknown_color_ac1100.Green = 0;
    unknown_color_ac1100.Blue = 0;
}
