// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_choice_dialog_proc_600d50@@YGHPAUHWND__@@IIJ@Z=00600d50
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_session_a3f616@@3_NA=00a3f616
// @ref ?unknown_counter_a3fabc@@3HA=00a3fabc
// @ref ?unknown_53f460@@YA_NXZ=0053f460
// @ref ?unknown_53fbd0@@YI_NXZ=0053fbd0
#include "shared/win32_api.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/lobby.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

bool __fastcall unknown_choice_dialog_600c80(unsigned short const *text)
{
    int result = -1;
    HWND dialog = unknown_create_dialog_5ff610(0x10d, unknown_choice_dialog_proc_600d50, 0);
    if (dialog) {
        HWND item = GetDlgItem(dialog, 0x5b0);
        SendMessageA(item, 0x4b2, 0, (LPARAM)text);
        SetWindowLongA(dialog, DWL_USER, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        while (result < 0) {
            Unknown_005B5EE0();
            if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5 && !unknown_session_a3f616 &&
                unknown_counter_a3fabc == 0 && !unknown_53f460() && unknown_53fbd0()) {
                break;
            }
        }
        unknown_dialog_5ff6e0(dialog);
    }
    return result == 0x5c1;
}
