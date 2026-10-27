// int __fastcall unknown_combo_selected_data(HWND dialog, int id, int index) -- 0x005C99D0
// Purpose: the item data (CB_GETITEMDATA) of combo box item `index` of a
// dialog control, using the current selection (CB_GETCURSEL) when `index`
// is -1; 0 instead of CB_ERR. No direct callers.
#include "shared/win32_api.hpp"
// @ref __imp__SendDlgItemMessageA@20=0079a484

WIN32_IMPORT long __stdcall SendDlgItemMessageA(HWND dialog, int id, unsigned int message, unsigned int wparam,
                                                long lparam);

int __fastcall unknown_combo_selected_data_005c99d0(HWND dialog, int id, int index)
{
    if (index == -1) {
        index = SendDlgItemMessageA(dialog, id, 0x147, 0, 0);     // CB_GETCURSEL
    }
    int data = SendDlgItemMessageA(dialog, id, 0x150, index, 0);  // CB_GETITEMDATA
    return data == -1 ? 0 : data;
}
