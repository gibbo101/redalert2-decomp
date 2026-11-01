// int __fastcall Dialog_Loop_007359e0(HWND dialog, bool (*callback)(), int unused, bool modal, bool show) (0x007359E0)
// @ref ?unknown_is_listed_b25bb8@@YIHH@Z=00735910
// @ref ?End_Dialog_007357e0@@YI_NPAUHWND__@@H@Z=007357e0
// @ref ?unknown_peek_message_522ed0@@YIHPAUtagMSG@@PAUHWND__@@III@Z=00522ed0
// @ref ?unknown_message_count_a52298@@3HA=00a52298
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?unknown_dialog_result_b25ddc@@3HA=00b25ddc
// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
#include "shared/win_util.hpp"
#include "shared/win32_window.hpp"

int __fastcall Dialog_Loop_007359e0(HWND dialog, bool (*callback)(), int unused, bool modal, bool show)
{
    if (modal) {
        SetForegroundWindow(dialog);
        SendMessageA(dialog, 0x4A9, 0, 1);
    }
    if (show) {
        ShowWindow(dialog, 1);
    }
    while (unknown_is_listed_b25bb8((int)dialog)) {
        if (callback != 0 && callback() == true) {
            End_Dialog_007357e0(dialog, 2);
        }
        if (!unknown_b2abd9) {
            unknown_517370(false);
        }
        unknown_message_count_a52298++;
        MSG message;
        while (unknown_peek_message_522ed0(&message, 0, 0, 0, 1)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
            if (!unknown_is_listed_b25bb8((int)dialog)) {
                break;
            }
        }
        Sleep(0);
    }
    if (modal) {
        SendMessageA(dialog, 0x4A9, 0, 0);
    }
    return unknown_dialog_result_b25ddc;
}
