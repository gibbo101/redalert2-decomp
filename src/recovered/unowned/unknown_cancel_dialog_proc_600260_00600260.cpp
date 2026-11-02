// int __stdcall unknown_cancel_dialog_proc_600260(HWND, UINT, WPARAM, LPARAM) (0x00600260)
// The cancel dialog's procedure: the default dialog handling first; its cancel button (0x5C0)
// sets the caller's flag (DWL_USER) and queues key 0x1B (Escape).
#include "shared/win32_api.hpp"
#include "shared/dialog_default_proc.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/keyboard.hpp"
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref __imp__GetWindowLongA@8=0079a48c

int __stdcall unknown_cancel_dialog_proc_600260(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }
    if (message == 0x111 && wparam == 0x5c0) {
        bool *cancelled = (bool *)GetWindowLongA(window, DWL_USER);
        if (cancelled) {
            WWKeyboard->Put((KeyNumType)0x1b);
            *cancelled = true;
        }
    }
    return 0;
}
