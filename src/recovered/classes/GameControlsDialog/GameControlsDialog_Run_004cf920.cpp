// void GameControlsDialog::Run() (0x004CF920)
// Logs the speed, scroll rate and detail level, shows the Game Controls dialog
// (0xBBB in a game, 0xF5 otherwise), waits until a button sets the result held
// in DWL_USER (-1 while waiting; the quit check ends it with 2), on OK (1) applies
// the settings and saves the options, and logs the values again.
#include "shared/game_controls_dialog.hpp"
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/ms_message_box.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Save_Settings@OptionsClass@@QAEXXZ=005d91b0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ??_C@_0DM@LBOA@GameControls?3?5GameSpeed?5?$DN?5?$CFd?0?5Sc@=007d849c
// @ref ?Apply_Settings@GameControlsDialog@@QAEXXZ=004cfa00
// @ref ?Game_Controls_Proc@@YGHPAUHWND__@@IIJ@Z=004cfc00

void GameControlsDialog::Run()
{
    int result = -1;
    Debug_Printf("GameControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n", Options.GameSpeed, Options.ScrollRate, Options.DetailLevel);
    if (unknown_flag_a40958 == 1) {
        Window = unknown_create_dialog_5ff610(0xBBB, Game_Controls_Proc, 0);
    } else {
        Window = unknown_create_dialog_5ff610(0xF5, Game_Controls_Proc, 0);
    }
    if (Window) {
        SetWindowLongA(Window, 8, (LONG)&result);
        unknown_dialog_5ff7c0(Window);
        while (result == -1) {
            if (unknown_6000d0() == true) {
                result = 2;
            }
            if (!unknown_flag_a40958) {
                unknown_517370(false);
            }
        }
        if (result == 1) {
            Apply_Settings();
            Options.Save_Settings();
        }
        unknown_dialog_5ff6e0(Window);
    }
    Debug_Printf("GameControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n", Options.GameSpeed, Options.ScrollRate, Options.DetailLevel);
}
