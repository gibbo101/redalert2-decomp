// Centres the dialog's movie control 0x71A in the 800x600 area of the screen
// (unknown_8523e0 x unknown_8523e4), starts it (0x4E3) and loads the large or, at
// 640 wide, the small Ra2ts clip (0x4E4) (0x005115F0; called by 0x005EAB60).
#include "shared/ms_message_box.hpp"
#include "shared/unknown_globals.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SetWindowPos@28=0079a3d0
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ??_C@_07CNEI@Ra2ts_l?$AA@=007db5a8
// @ref ??_C@_07IFGF@Ra2ts_s?$AA@=007db5b0

void __fastcall unknown_5115f0(HWND dialog)
{
    HWND control = GetDlgItem(dialog, 0x71A);
    if (control != 0) {
        int x = unknown_8523e0 <= 800 ? 0 : (unknown_8523e0 - 800) / 2;
        int y = unknown_8523e4 <= 600 ? 0 : (unknown_8523e4 - 600) / 2;
        SetWindowPos(control, 0, x, y, -1, -1, 0xD);     // SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW
        SendMessageA(control, 0x4E3, 1, 0);
        if (unknown_8523e0 == 640) {
            SendMessageA(control, 0x4E4, 0, (LPARAM)"Ra2ts_s");
        } else {
            SendMessageA(control, 0x4E4, 0, (LPARAM)"Ra2ts_l");
        }
    }
}
