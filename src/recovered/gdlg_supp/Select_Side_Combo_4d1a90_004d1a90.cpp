// void __fastcall Select_Side_Combo_4d1a90(HWND dialog, int id, int side) (0x004D1A90)
// Selects a country in a player row's side combo box and shows its flag.
// The box is hidden while it changes when it was visible.
#include "shared/gdlg_supp.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendDlgItemMessageA@20=0079a484

void __fastcall Select_Side_Combo_4d1a90(HWND dialog, int id, int side)
{
    HWND combo = GetDlgItem(dialog, id);
    bool hidden = ShowWindow(combo, SW_HIDE) == 0;
    int count = SendDlgItemMessageA(dialog, id, CB_GETCOUNT, 0, 0);
    for (int item = 0; item < count; item++) {
        if (SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, item, 0) == side) {
            SendDlgItemMessageA(dialog, id, CB_SETCURSEL, item, 0);
            break;
        }
    }
    if (!hidden) {
        ShowWindow(combo, SW_SHOW);
    }
    Show_Player_Flag_4d1230(dialog, Side_Combo_Player_4d13b0(id));
}
