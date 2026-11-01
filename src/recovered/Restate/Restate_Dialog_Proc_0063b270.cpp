// int __stdcall Restate_Dialog_Proc_0063b270(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
// -- 0x0063B270 (Restate.cpp): the briefing dialog: 0x497 loads the text into control 0x6E7;
// button 0x423 stores its id through the DWL_USER pointer.
#include "shared/ms_message_box.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Restate_Text_00ab66e8@@3PBGB=00ab66e8

extern wchar_t const *Restate_Text_00ab66e8;

int __stdcall Restate_Dialog_Proc_0063b270(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497: {
            HWND item = GetDlgItem(window, 0x6E7);
            SendMessageA(item, 0x4B2, 0, (LPARAM)Restate_Text_00ab66e8);
            return 0;
        }
        case 0x111:
            if (GetDlgCtrlID((HWND)lparam) == 0x423 && (unsigned short)(wparam >> 16) == 0) {   // HIWORD(wparam) == BN_CLICKED
                *(int *)GetWindowLongA(window, 8) = 0x423;
            }
            break;
    }
    return 0;
}
