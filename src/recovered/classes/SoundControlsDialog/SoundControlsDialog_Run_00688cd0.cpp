// void SoundControlsDialog::Run_00688CD0() (0x00688CD0)
// TS SoundControlsClass::Dialog: shows the sound controls (a cut down dialog outside a game) and services
// the owner draw dialog handler until the player dismisses them.
#include "shared/sound_controls.hpp"
#include "shared/dialog_create.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/debug_printf.hpp"
#include "shared/options.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?DialogInitialized@SoundControlsDialog@@2_NA=00abcfb0
// @ref ?Sound_Option_Dialog_Func@SoundControlsDialog@@SGHPAUHWND__@@IIJ@Z=00688da0
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ??_C@_0DN@NFFC@SoundControls?3?5GameSpeed?5?$DN?5?$CFd?0?5S@=007f4288

void SoundControlsDialog::Run_00688CD0()
{
    int rc = -1;
    Debug_Printf("SoundControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n", Options.GameSpeed,
                 Options.ScrollRate, Options.DetailLevel);
    DialogInitialized = false;

    HWND dialog;
    if (!unknown_flag_a40958) {
        dialog = unknown_create_dialog_5ff610(0xD6, Sound_Option_Dialog_Func, 0);
    } else {
        dialog = unknown_create_dialog_5ff610(0xB8, Sound_Option_Dialog_Func, 0);
    }

    if (dialog) {
        SetWindowLongA(dialog, 8, (LONG)&rc);
        unknown_dialog_5ff7c0(dialog);
        while (rc == -1) {
            if (unknown_6000d0() == true) {
                rc = 2;
            }
            if (!unknown_flag_a40958) {
                unknown_517370(false);
            }
        }
        unknown_dialog_5ff6e0(dialog);
    }

    Debug_Printf("SoundControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n", Options.GameSpeed,
                 Options.ScrollRate, Options.DetailLevel);
}
