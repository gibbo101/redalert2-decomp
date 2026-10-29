// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref __imp__GetWindowLongA@8=0079a48c
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

int __stdcall unknown_choice_dialog_proc_600d50(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }
    int *choice = (int *)GetWindowLongA(window, DWL_USER);
    if (message == 0x111) {
        int id = wparam & 0xffff;
        if (id >= 0x5c0 && id <= 0x5c1) {
            *choice = id;
        }
    }
    return 0;
}
