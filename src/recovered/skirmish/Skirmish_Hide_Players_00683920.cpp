// void __fastcall Skirmish_Hide_Players(HWND dialog, int first) (0x00683920)
// Sets the players from `first` on to "none" (item data -1), updates their
// colour and side boxes, then hides their rows.
#include "shared/skirmish.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Skirmish_Hide_Players(HWND dialog, int first)
{
    int player;
    for (player = first; player < 8; player++) {
        int combo = Skirmish_Player_Combo_ID(player - 1);
        int count = SendDlgItemMessageA(dialog, combo, CB_GETCOUNT, 0, 0);
        for (int item = 0; item < count; item++) {
            if (SendDlgItemMessageA(dialog, combo, CB_GETITEMDATA, item, 0) == -1) {
                SendDlgItemMessageA(dialog, combo, CB_SETCURSEL, item, 0);
                break;
            }
        }
        int row = Skirmish_Player_Index(combo) + 1;
        int row_color = Player_Color_Combo_ID_4d1cb0(row);
        int row_side = Player_Side_Combo_ID_4d1350(row);
        int selection = SendDlgItemMessageA(dialog, combo, CB_GETCURSEL, 0, 0);
        int type = SendDlgItemMessageA(dialog, combo, CB_GETITEMDATA, selection, 0);
        bool enable = type == 0 || type == 1 || type == 2;
        if (!enable) {
            Select_Color_Combo_4d2480(dialog, row_color, -2);
            Select_Side_Combo_4d1a90(dialog, row_side, -2);
        }
        HWND color_box = GetDlgItem(dialog, row_color);
        HWND side_box = GetDlgItem(dialog, row_side);
        EnableWindow(color_box, enable);
        EnableWindow(side_box, enable);
    }
    for (player = first; player < 8; player++) {
        int combo = Skirmish_Player_Combo_ID(player - 1);
        int row_id = unknown_player_control_4d0ee0(player);
        int side_id = Player_Side_Combo_ID_4d1350(player);
        int color_id = Player_Color_Combo_ID_4d1cb0(player);
        HWND combo_window = GetDlgItem(dialog, combo);
        HWND row_window = GetDlgItem(dialog, row_id);
        HWND side_window = GetDlgItem(dialog, side_id);
        HWND color_window = GetDlgItem(dialog, color_id);
        ShowWindow(combo_window, SW_HIDE);
        ShowWindow(row_window, SW_HIDE);
        ShowWindow(side_window, SW_HIDE);
        ShowWindow(color_window, SW_HIDE);
    }
}

// @ref ?unknown_player_control_4d0ee0@@YIHH@Z=004d0ee0
// @ref ?Player_Side_Combo_ID_4d1350@@YIHH@Z=004d1350
// @ref ?Player_Color_Combo_ID_4d1cb0@@YIHH@Z=004d1cb0
// @ref ?Select_Color_Combo_4d2480@@YIXPAUHWND__@@HH@Z=004d2480
// @ref ?Select_Side_Combo_4d1a90@@YIXPAUHWND__@@HH@Z=004d1a90
