// void Unknown_Init_Sidebar_Art_006F4400() (0x006F4400)
// Loads the sidebar art unconditionally: the art buffers (0x006F4B00), the
// SIDEBAR/UIBKGD palettes of 0x006F4C60 expanded inline and the layout for the
// screen size (0x006F4C90), then marks the art loaded (the block that
// 0x006F4620 runs when the flag is clear).
// @ref ?unknown_flag_ac11b0@@3_NA=00ac11b0
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_value_8523e4@@3HA=008523e4
// @ref ?Unknown_Load_Art_Buffers_006F4B00@@YIXXZ=006f4b00

void __fastcall Unknown_Load_Art_Buffers_006F4B00();
void __fastcall Unknown_Load_Art_Pairs_006F4C60();
void __fastcall Unknown_Layout_Sidebar_006F4C90(int width, int height);
extern bool unknown_flag_ac11b0;
extern int unknown_value_8523e0;                 // screen width
extern int unknown_value_8523e4;                 // screen height

void __fastcall Unknown_Init_Sidebar_Art_006F4400()
{
    Unknown_Load_Art_Buffers_006F4B00();
    Unknown_Load_Art_Pairs_006F4C60();
    Unknown_Layout_Sidebar_006F4C90(unknown_value_8523e0, unknown_value_8523e4);
    unknown_flag_ac11b0 = true;
}
