// int __fastcall unknown_select_list_item_by_data(HWND dialog, int data) -- 0x005C7160
// Purpose: in list box control 0x553 of a dialog, finds the last item whose
// item data (LB_GETITEMDATA) equals `data`, selects it (LB_SETCURSEL),
// scrolls it to the top (LB_SETTOPINDEX) and returns its index (item 0 when
// none matches); -1 when `data` is 0. No direct callers.
#include "shared/win32_api.hpp"
// @ref __imp__SendDlgItemMessageA@20=0079a484

WIN32_IMPORT long __stdcall SendDlgItemMessageA(HWND dialog, int id, unsigned int message, unsigned int wparam,
                                                long lparam);

int __fastcall unknown_select_list_item_by_data_005c7160(HWND dialog, int data)
{
    if (data == 0) {
        return -1;
    }
    int found = 0;
    int count = SendDlgItemMessageA(dialog, 0x553, 0x18b, 0, 0);       // LB_GETCOUNT
    for (int index = 0; index < count; index++) {
        if (SendDlgItemMessageA(dialog, 0x553, 0x199, index, 0) == data) {   // LB_GETITEMDATA
            found = index;
        }
    }
    SendDlgItemMessageA(dialog, 0x553, 0x186, found, 0);   // LB_SETCURSEL
    SendDlgItemMessageA(dialog, 0x553, 0x197, found, 0);   // LB_SETTOPINDEX
    return found;
}
