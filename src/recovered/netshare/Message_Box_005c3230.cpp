// int __fastcall Message_Box_005c3230(wchar_t const *text, int kind, bool (*callback)(), bool flag) (0x005C3230)
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
// @ref ?Unknown_005e8fa0@@YIXPAUHWND__@@@Z=005e8fa0
// @ref ?Unknown_007359e0@@YIHPAUHWND__@@P6A_NXZHHH@Z=007359e0

int __fastcall Message_Box_005c3230(wchar_t const *text, int kind, bool (*callback)(), bool flag)
{
    if (text == 0 || wcslen(text) == 0) {
        return 0;
    }
    int id;
    if (flag) {
        id = 0xfb;
    } else if (kind == 0) {
        id = 0xd0;
    } else if (kind == 1) {
        id = 0xfc;
    } else {
        id = kind == 4 ? 0x126 : 0xfb;
    }
    HWND dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, id, (HWND)unknown_b263d8, Unknown_Dialog_Proc_005c33a0, 0);
    unknown_show_dialog_5ff7e0(dialog, id);
    HWND button;
    if (kind == 0) {
        button = GetDlgItem(dialog, 1);
        SetWindowLongA(button, -16, GetWindowLongA(button, -16) | 0x10000000);      // WS_VISIBLE
        if (flag) {
            Unknown_005e8fa0(button);
        }
    } else if (kind == 1) {
        button = GetDlgItem(dialog, 1);
        SetWindowLongA(button, -16, GetWindowLongA(button, -16) | 0x10000000);
        button = GetDlgItem(dialog, 2);
        SetWindowLongA(button, -16, GetWindowLongA(button, -16) | 0x10000000);
    } else if (kind == 4) {
        button = GetDlgItem(dialog, 6);
        SetWindowLongA(button, -16, GetWindowLongA(button, -16) | 0x10000000);
        button = GetDlgItem(dialog, 7);
        SetWindowLongA(button, -16, GetWindowLongA(button, -16) | 0x10000000);
    }
    HWND message = GetDlgItem(dialog, 0x5b0);
    SendMessageA(message, 0x4b2, 0, (LPARAM)text);
    ShowWindow(dialog, 1);
    return Unknown_007359e0(dialog, callback, 0, 1, 1);
}
