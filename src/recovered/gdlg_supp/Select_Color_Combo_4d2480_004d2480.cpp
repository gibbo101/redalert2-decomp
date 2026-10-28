// void __fastcall Select_Color_Combo_4d2480(HWND dialog, int id, int color) (0x004D2480)
// Selects a colour in a player row's colour combo box: the row gives up the
// colour it held, takes the new one (unless it is random, -2), and every
// row's colour list is refilled. The box is hidden while it changes when it
// was visible.
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref ?unknown_color_entries_8660d8@@3PAUUnknownColorEntry@@A=008660d8
// @ref ?Fill_Color_Combo_4d2080@@YIXPAUHWND__@@H@Z=004d2080

void __fastcall Select_Color_Combo_4d2480(HWND dialog, int id, int color)
{
    HWND combo = GetDlgItem(dialog, id);
    bool hidden = ShowWindow(combo, SW_HIDE) == 0;
    int entry = Color_Entry_Of_Combo_4d1fc0(id);
    if (entry != -1) {
        unknown_color_entries_8660d8[entry].Index = -1;
    }
    int count = SendDlgItemMessageA(dialog, id, CB_GETCOUNT, 0, 0);
    for (int item = 0; item < count; item++) {
        int data = SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, item, 0);
        if (data == color) {
            SendDlgItemMessageA(dialog, id, CB_SETCURSEL, item, 0);
            if (data != -2) {
                unknown_color_entries_8660d8[data].Index = Color_Combo_Player_4d1d10(id);
            }
            break;
        }
    }
    if (!hidden) {
        ShowWindow(combo, SW_SHOW);
    }
    Fill_Color_Combos_4d2300(dialog);
}
