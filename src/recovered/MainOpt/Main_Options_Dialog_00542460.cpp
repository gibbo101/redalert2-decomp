// void __fastcall Main_Options_Dialog() (0x00542460)
// Runs the shell Options dialog 0xD5 over and over: keeps a copy of Options, applies the controls when it
// closes, and for 0x5CD shows dialog 0xD7 (after reading the multiplayer settings), for 0x5CE the dialog
// of 0x005DA360; any other result ends it with the options saved. Plays with the game flag cleared.
#include "shared/main_opt.hpp"
#include "shared/session_state.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?unknown_options_a6ec38@@3VOptionsClass@@A=00a6ec38
// @ref ?Save_Settings@OptionsClass@@QAEXXZ=005d91b0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?Main_Options_Apply@@YIXPAUHWND__@@@Z=00542280
// @ref ?Main_Options_Proc@@YGHPAUHWND__@@IIJ@Z=00542590
// @ref ?Main_Options_Proc2@@YGHPAUHWND__@@IIJ@Z=00542d60
// @ref ?Unknown_005DA360@OptionsClass@@QAE_NXZ=005da360
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298

void __fastcall Main_Options_Dialog()
{
    bool game_flag = unknown_flag_a40958;
    int result;
    unknown_flag_a40958 = false;
    for (;;) {
        unknown_options_a6ec38 = Options;
        result = -1;
        HWND dialog = unknown_create_dialog_5ff610(0xD5, Main_Options_Proc, 0);
        if (!dialog) {
            continue;
        }
        SetWindowLongA(dialog, 8, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        while (result < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            unknown_517370(false);
        }
        Main_Options_Apply(dialog);
        unknown_dialog_5ff6e0(dialog);
        switch (result) {
            case 0x5CD: {
                int confirm = -1;
                unknown_session_a3d298.Read_MultiPlayer_Settings();
                dialog = unknown_create_dialog_5ff610(0xD7, Main_Options_Proc2, 0);
                if (dialog) {
                    SetWindowLongA(dialog, 8, (LONG)&confirm);
                    unknown_dialog_5ff7c0(dialog);
                    while (confirm < 0) {
                        if (unknown_6000d0() == true) {
                            break;
                        }
                        unknown_517370(false);
                    }
                    unknown_dialog_5ff6e0(dialog);
                }
                continue;
            }
            case 0x5CE:
                Options.Unknown_005DA360();
                continue;
            default:
                Options.Save_Settings();
                unknown_flag_a40958 = game_flag;
                return;
        }
    }
}
