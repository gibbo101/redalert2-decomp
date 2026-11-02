// The delete game dialog's procedure: owner-draw first, then the list columns and the command handler (0x0053B650).
#include "shared/load_dlg.hpp"

LRESULT __stdcall LoadOptionsClass::Delete_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
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
        Delete_Dialog_On_WM_COMMAND(window, (unsigned short)wparam, (HWND)lparam, (unsigned short)(wparam >> 16));
        break;
    case 0x216:
        return Unknown_Clamp_Rect_To_Screen_00736D80(window, wparam, (Rect *)lparam);
    case 0x497:
        SendDlgItemMessageA(window, 0x528, 0x4a6, 0xf9, 2);
        SendDlgItemMessageA(window, 0x528, 0x4a6, 0x38, 0xff);
        SendDlgItemMessageA(window, 0x528, 0x4a6, 0, 0x13b);
        break;
    }
    return 0;
}
