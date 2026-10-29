// bool __fastcall Try_Mode_Dialog() (0x00542210)
// Shows the "about to try mode" dialog 0xD9 and waits for a button or the quit check;
// true when the first button (result 1) was pressed.
#include "shared/main_opt.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?Try_Mode_Proc@@YGHPAUHWND__@@IIJ@Z=00542160

bool __fastcall Try_Mode_Dialog()
{
    int result = -1;
    HWND dialog = unknown_create_dialog_5ff610(0xD9, Try_Mode_Proc, 0);
    if (dialog) {
        SetWindowLongA(dialog, 8, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        while (result < 0) {
            if (unknown_6000d0()) {
                break;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(dialog);
    }
    return result == 1;
}
