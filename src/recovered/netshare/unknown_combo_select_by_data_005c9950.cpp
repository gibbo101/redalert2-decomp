// void __fastcall unknown_combo_select_by_data(HWND dialog, int id, int data) -- 0x005C9950
// Purpose: hides a dialog combo box while it selects (CB_SETCURSEL) the first
// item whose item data (CB_GETITEMDATA) equals `data`, then shows it again.
// Its one caller in the unit, 0x005CC700, expands it inline.
#include "shared/win32_api.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendDlgItemMessageA@20=0079a484

WIN32_IMPORT HWND __stdcall GetDlgItem(HWND dialog, int id);
WIN32_IMPORT BOOL __stdcall ShowWindow(HWND window, int command);
WIN32_IMPORT long __stdcall SendDlgItemMessageA(HWND dialog, int id, unsigned int message, unsigned int wparam,
                                                long lparam);

void __fastcall unknown_combo_select_by_data_005c9950(HWND dialog, int id, int data)
{
    HWND combo = GetDlgItem(dialog, id);
    ShowWindow(combo, 0);                                           // SW_HIDE
    int count = SendDlgItemMessageA(dialog, id, 0x146, 0, 0);       // CB_GETCOUNT
    for (int index = 0; index < count; index++) {
        if (SendDlgItemMessageA(dialog, id, 0x150, index, 0) == data) {   // CB_GETITEMDATA
            SendDlgItemMessageA(dialog, id, 0x14e, index, 0);              // CB_SETCURSEL
            break;
        }
    }
    ShowWindow(combo, 5);                                           // SW_SHOW
}
