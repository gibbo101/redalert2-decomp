// int __stdcall Message_Box_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x005B48C0)
// Dialog procedure of the message box: the shared handler first, then
// WM_COMMAND (Message_Box_Command, expanded inline) and WM_MOVING.
#include "shared/ms_message_box.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_moving_736d80@@YI_NPAUHWND__@@IJ@Z=00736d80

int __stdcall Message_Box_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x111:
            Message_Box_Command(window, wparam & 0xFFFF, (HWND)lparam, wparam >> 16);
            break;
        case 0x216:
            return unknown_moving_736d80(window, wparam, lparam);
    }
    return 0;
}
