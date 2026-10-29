// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_cancel_dialog_proc_600260@@YGHPAUHWND__@@IIJ@Z=00600260
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__ShowWindow@8=0079a498
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

HWND __fastcall unknown_cancel_dialog_6001e0(unsigned short const *text, unsigned short const *button, bool *cancelled)
{
    HWND dialog = unknown_create_dialog_5ff610(0xf0, unknown_cancel_dialog_proc_600260, 0);
    if (dialog) {
        SetWindowLongA(dialog, DWL_USER, (LONG)cancelled);
        HWND label = GetDlgItem(dialog, 0x5b0);
        SendMessageA(label, 0x4b2, 0, (LPARAM)text);
        if (button) {
            HWND item = GetDlgItem(dialog, 0x5c0);
            SendMessageA(item, 0x4b2, 0, (LPARAM)button);
            EnableWindow(item, TRUE);
            ShowWindow(item, SW_SHOW);
        }
    }
    return dialog;
}
