// The save game dialog's procedure: owner-draw first, then the list columns and the command handler (0x0053B530).
#include "shared/load_dlg.hpp"

LRESULT __stdcall LoadOptionsClass::Save_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    switch (message) {
    case 0x0f:
        unknown_dialog_5e5f20(window);
        return 1;
    case 0x111:
        Save_Dialog_On_WM_COMMAND(window, (unsigned short)wparam, (HWND)lparam, (unsigned short)(wparam >> 16));
        break;
    case 0x216:
        return Unknown_Clamp_Rect_To_Screen_00736D80(window, wparam, (Rect *)lparam);
    case 0x497:
        SendMessageA(GetDlgItem(window, 0x526), 0xc5, 0x4f, 0);
        SendDlgItemMessageA(window, 0x527, 0x4a6, 0xf9, 2);
        SendDlgItemMessageA(window, 0x527, 0x4a6, 0x38, 0xff);
        SendDlgItemMessageA(window, 0x527, 0x4a6, 0, 0x13b);
        break;
    case 0x4da:
        ((LoadOptionsClass *)GetWindowLongA(window, 8))->State = 1;
        break;
    }
    return 0;
}
