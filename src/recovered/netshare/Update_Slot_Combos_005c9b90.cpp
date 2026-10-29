// void __fastcall Unknown_005c9b90(HWND dialog, int slot, bool redraw) (0x005C9B90)
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Unknown_005c9b90(HWND dialog, int slot, bool redraw)
{
    int side_id = Player_Side_Combo_ID_4d1350(slot);
    int color_id = Player_Color_Combo_ID_4d1cb0(slot);
    if (unknown_lobby_flag_7e6d90 >= 0 && slot == unknown_lobby_flag_7e6d90
        && (unknown_player_slots_a3fa98[slot] == unknown_player_a72d44 || slot == 0
            || unknown_player_slots_a3fa98[slot]->Team == -1)) {
        Select_Side_Combo_4d1a90(dialog, side_id, -3);
        Select_Color_Combo_4d2480(dialog, color_id, -2);
        HWND side = GetDlgItem(dialog, side_id);
        EnableWindow(side, FALSE);
        HWND control = GetDlgItem(dialog, color_id);
        EnableWindow(control, FALSE);
        ShowWindow(control, 0);
        return;
    }
    if (!redraw) {
        Select_Side_Combo_4d1a90(dialog, side_id, -2);
        Select_Color_Combo_4d2480(dialog, color_id, -2);
    }
    HWND side = GetDlgItem(dialog, side_id);
    EnableWindow(side, redraw);
    HWND control = GetDlgItem(dialog, color_id);
    EnableWindow(control, redraw);
    int limit = Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4);
    if (unknown_lobby_flag_7e6d90 == 0 && limit < 7) {
        limit++;
    }
    if (slot < limit || slot == unknown_lobby_flag_7e6d90) {
        ShowWindow(control, 5);
    }
}
