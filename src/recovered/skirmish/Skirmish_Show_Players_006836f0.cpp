// void __fastcall Skirmish_Show_Players(HWND dialog, int first, int count) (0x006836F0)
// Shows the rows of players first..first+count-1; their colour and side boxes
// are enabled for computer players and reset (-2) for the others.
#include "shared/skirmish.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Skirmish_Show_Players(HWND dialog, int first, int count)
{
    for (int player = first; player < first + count; player++) {
        int combo = Skirmish_Player_Combo_ID(player - 1);
        int row_id = unknown_player_control_4d0ee0(player);
        int color_id = Player_Color_Combo_ID_4d1cb0(player);
        int side_id = Player_Side_Combo_ID_4d1350(player);
        HWND combo_window = GetDlgItem(dialog, combo);
        HWND row_window = GetDlgItem(dialog, row_id);
        HWND color_window = GetDlgItem(dialog, color_id);
        HWND side_window = GetDlgItem(dialog, side_id);
        ShowWindow(combo_window, SW_SHOW);
        ShowWindow(row_window, SW_SHOW);
        ShowWindow(color_window, SW_SHOW);
        ShowWindow(side_window, SW_SHOW);
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
}

// @ref ?unknown_player_control_4d0ee0@@YIHH@Z=004d0ee0
// @ref ?Player_Side_Combo_ID_4d1350@@YIHH@Z=004d1350
// @ref ?Player_Color_Combo_ID_4d1cb0@@YIHH@Z=004d1cb0
// @ref ?Select_Color_Combo_4d2480@@YIXPAUHWND__@@HH@Z=004d2480
// @ref ?Select_Side_Combo_4d1a90@@YIXPAUHWND__@@HH@Z=004d1a90
