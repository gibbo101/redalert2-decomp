// int __fastcall Color_Combo_Data_4d2900(HWND dialog, int id, int index) (0x004D2900)
// The item data of the colour combo box's item index (-1: the selection).
#include "shared/gdlg_supp.hpp"
// @ref __imp__SendDlgItemMessageA@20=0079a484

int __fastcall Color_Combo_Data_4d2900(HWND dialog, int id, int index)
{
    if (index == -1) {
        index = SendDlgItemMessageA(dialog, id, CB_GETCURSEL, 0, 0);
    }
    return SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, index, 0);
}
