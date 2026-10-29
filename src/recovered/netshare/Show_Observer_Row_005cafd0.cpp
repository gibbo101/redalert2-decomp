// void __fastcall Unknown_005cafd0(HWND dialog) (0x005CAFD0)
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

void __fastcall Unknown_005cafd0(HWND dialog)
{
    int slot = unknown_lobby_flag_7e6d90;
    if (slot < 0) {
        return;
    }
    if (slot == 0) {
        slot = unknown_int_a3db1c;
    }
    if (slot >= 8) {
        return;
    }
    int color_id;
    int slot_id;
    if (slot == 0) {
        color_id = 0x6D2;
        slot_id = 0x411;
    } else if (slot == 1) {
        color_id = 0x6D3;
        slot_id = 0x412;
    } else if (slot == 2) {
        color_id = 0x6D4;
        slot_id = 0x413;
    } else if (slot == 3) {
        color_id = 0x6D5;
        slot_id = 0x414;
    } else if (slot == 4) {
        color_id = 0x6D6;
        slot_id = 0x415;
    } else if (slot == 5) {
        color_id = 0x6D7;
        slot_id = 0x416;
    } else if (slot == 6) {
        color_id = 0x6D8;
        slot_id = 0x417;
    } else if (slot == 7) {
        color_id = 0x6D9;
        slot_id = 0x418;
    } else {
        color_id = -1;
        slot_id = -1;
    }
    int player_id = unknown_player_control_4d0ee0(slot);
    int color_combo_id = Player_Color_Combo_ID_4d1cb0(slot);
    int side_combo_id = Player_Side_Combo_ID_4d1350(slot);
    NodeNameType *entry = unknown_player_slots_a3fa98[slot];
    bool observer;
    if (entry == unknown_player_a72d44 || (entry != 0 && entry != unknown_open_entry_a72d2c
        && entry != unknown_closed_entry_a72d30 && entry != unknown_waiting_entry_a72d40 && entry->Team == -1)) {
        observer = true;
    } else {
        observer = false;
    }
    HWND color = GetDlgItem(dialog, color_id);
    HWND combo = GetDlgItem(dialog, slot_id);
    HWND player = GetDlgItem(dialog, player_id);
    HWND color_combo = GetDlgItem(dialog, color_combo_id);
    HWND side_combo = GetDlgItem(dialog, side_combo_id);
    ShowWindow(color, 5);
    ShowWindow(combo, 5);
    ShowWindow(player, 5);
    if (!observer) {
        ShowWindow(color_combo, 5);
        ShowWindow(side_combo, 5);
    } else {
        ShowWindow(color_combo, 0);
        ShowWindow(side_combo, 5);
    }
}
