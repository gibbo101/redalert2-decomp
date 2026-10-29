// Undoes 0x00672DE0.
void UnknownSessionState::Unknown_00672E70()
{
    if (unknown_3080) {
        unknown_3080 = false;
        if (unknown_game_speed_7f3230 != -1) {
            Options.GameSpeed = unknown_game_speed_7f3230;
            unknown_game_speed_7f3230 = -1;
        }
        Unknown_005173A0();
        Unknown_005A09E0();
        Audio_Stop();
        Unknown_00714410();
        Speech_Reset();
        Unknown_007160D0();
        Audio_Global_Levels[7]->Volume.Set(0x4000);
        if (ToolTips) {
            ToolTips->Enable(false);
        }
        if (WWMouse->Is_Captured()) {
            WWMouse->Release_Mouse();
        }
        WWMouse->Hide_Mouse();
        unknown_ab9174 = 0;
    }
}
// @ref ?unknown_game_speed_7f3230@@3HA=007f3230
// @ref ?Unknown_005173A0@@YAXXZ=005173a0
