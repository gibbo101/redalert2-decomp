// int __stdcall Confirm_Mode_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x00543C40)
// The display mode confirmation dialog: 0x497 loads its text into control 0x5DB; the buttons
// 0x5C1 and 0x6CA store 1 and 2 through the DWL_USER pointer.
#include "shared/main_opt.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@OMLL@D?3?2Ra2?2MainOpt?4cpp?$AA@=007dfde0
// @ref ??_C@_0BG@CDBK@GUI?3ConfirmModeChange?$AA@=007e00ac

int __stdcall Confirm_Mode_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    int *result = (int *)GetWindowLongA(window, 8);
    switch (message) {
        case 0x497: {
            wchar_t const *text = StringTable::Load_String("GUI:ConfirmModeChange", 0, "D:\\Ra2\\MainOpt.cpp", 0x5D5);
            HWND item = GetDlgItem(window, 0x5DB);
            SendMessageA(item, 0x4B2, 0, (LPARAM)text);
            break;
        }
        case 0x111:
            switch ((unsigned short)wparam) {
                case 0x5C1:
                    *result = 1;
                    break;
                case 0x6CA:
                    *result = 2;
                    break;
            }
            break;
    }
    return 0;
}
