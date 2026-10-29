// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_5115f0@@YIXPAUHWND__@@@Z=005115f0
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/campaign_score.hpp"


int __fastcall unknown_dialog_box_5eab60(int resource, int (__stdcall *proc)(struct HWND__ *, unsigned int, unsigned int, long), bool show_5115f0)
{
    HWND dialog = unknown_create_dialog_5ff610(resource, proc, 0);
    int result = 0;
    if (dialog) {
        SetWindowLongA(dialog, DWL_USER, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        if (show_5115f0) {
            unknown_5115f0(dialog);
        }
        while (result == 0) {
            if (unknown_6000d0()) {
                break;
            }
        }
        unknown_dialog_5ff6e0(dialog);
    }
    return result;
}
