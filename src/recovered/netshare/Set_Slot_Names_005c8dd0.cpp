// void Set_Slot_Names_005c8dd0(wchar_t const *names) (0x005C8DD0)
// Seats a comma-separated list of lobby names in the player slots (the host's slot list): the
// slots are refilled (Fill_Slots), then each name takes the next slot (an unknown name waits).
// A slot that changes between observer (OpenObserver or a player of team -1) and player
// rebuilds its side and colour combo boxes in the setup dialog (0xC2, 0xC9, 0xBC or 0xBD).
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/crt_tokens.hpp"
// @ref ??_C@_13JKDK@?$AA?0?$AA?$AA@=007e5c64

void __fastcall Set_Slot_Names_005c8dd0(wchar_t const *names)
{
    if (*names == 0) {
        return;
    }
    wchar_t buffer[170];
    wcscpy(buffer, names);
    bool observer[8];
    NodeNameType *observer_entry = unknown_player_a72d44;
    NodeNameType *waiting = unknown_waiting_entry_a72d40;
    NodeNameType *open = unknown_open_entry_a72d2c;
    NodeNameType *closed = unknown_closed_entry_a72d30;
    for (int i = 0; i < 8; i++) {
        NodeNameType *entry = unknown_player_slots_a3fa98[i];
        observer[i] = entry == observer_entry
            || (entry != 0 && entry != open && entry != closed && entry != waiting && entry->Team == -1);
    }
    Fill_Slots_005c8a10();
    int slot = 0;
    for (wchar_t *name = wcstok(buffer, L","); name != 0; name = wcstok(0, L",")) {
        NodeNameType *entry;
        {
            WideString text(name);
            entry = Unknown_Find_Lobby_Entry_005cd1b0(text);
        }
        if (entry == 0) {
            entry = Unknown_Find_Lobby_Name_005c8b20(name);
            if (entry == 0) {
                entry = unknown_waiting_entry_a72d40;
            }
        }
        if (entry == unknown_player_a72d44
            || (entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30
                && entry != unknown_waiting_entry_a72d40 && entry != unknown_easy_ai_entry_a72d34
                && entry != unknown_medium_ai_entry_a72d38 && entry != unknown_hard_ai_entry_a72d3c
                && entry->Team == -1)) {
            HWND dialog = Find_Lobby_Window_005c2c40();
            if (!observer[slot]) {
                unknown_player_slots_a3fa98[slot] = entry;
                Fill_Observer_Combo_4d1640(dialog, Player_Side_Combo_ID_4d1350(slot));
                SendMessageA(GetDlgItem(dialog, Slot_Control_Id_005c97a0(slot)), 0x4F1, 0, 1);
                int id = Player_Color_Combo_ID_4d1cb0(slot);
                Fill_Random_Color_Combo_4d2250(dialog, id);
                Select_Color_Combo_4d2480(dialog, id, 8);
            }
        } else {
            HWND dialog = Find_Lobby_Window_005c2c40();
            if (observer[slot]) {
                int id = Player_Side_Combo_ID_4d1350(slot);
                if (Side_Combo_Data_4d1c70(dialog, id, -1) == -3) {
                    Fill_Side_Combo_4d1560(dialog, id);
                    SendMessageA(GetDlgItem(dialog, Slot_Control_Id_005c97a0(slot)), 0x4F1, 0, 0);
                    id = Player_Color_Combo_ID_4d1cb0(slot);
                    Fill_Color_Combo_4d2080(dialog, id);
                    Select_Color_Combo_4d2480(dialog, id, -2);
                }
            }
        }
        unknown_player_slots_a3fa98[slot] = entry;
        slot++;
    }
}
