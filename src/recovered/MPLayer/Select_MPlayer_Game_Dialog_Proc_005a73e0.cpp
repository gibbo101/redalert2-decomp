// int __stdcall Select_MPlayer_Game_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x005A73E0)
// The common dialog handler first; WM_COMMAND stores the control id in the int that DWL_USER points at
// (TibSun mplayer.cpp's Select_MPlayer_Game_Dialog_Proc without its WM_INITDIALOG part).
#include "shared/ms_message_box.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00

int __stdcall Select_MPlayer_Game_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int *retval;

    int rc = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (rc != 0) {
        return rc;
    }

    if (message == 0x111) {
        retval = (int *)GetWindowLongA(window, DWL_USER);
        *retval = (unsigned short)wparam;
    }
    return 0;
}
