// void __fastcall Unknown_005ca6c0(HWND dialog) (0x005CA6C0)
// Refills the eight slot combo boxes (0x411..0x418): each lists its current entry (open, closed, AI levels,
// waiting, open observer or a player's name); the host also gets the choices for the slot (open within the
// slot limit, open observer for the local slot, closed, and the AI levels when computer players are allowed).
// Each combo is hidden while it is refilled and its current text selected again.
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"


// Adds a row with the given text to a slot combo box (0x4C2) and stores the slot entry as its item data.
// The entry is taken by reference: it is read after the row is added (the globals' loads follow the call).
static inline void Add_Combo_Entry(HWND combo, wchar_t const *text, NodeNameType * const &entry)
{
    int index = SendMessageA(combo, 0x4C2, 0, (LPARAM)text);
    SendMessageA(combo, CB_SETITEMDATA, index, (LPARAM)entry);
}

void __fastcall Unknown_005ca6c0(HWND dialog)
{
    bool ai_allowed = (unknown_session_a3d29c == 0 || unknown_session_a3d29c->unknown_slot12()) && !unknown_73c370();
    int limit = Lobby_Slot_Limit_005c6520();
    if (unknown_lobby_flag_7e6d90 == 0) {
        if (ai_allowed || limit < Lobby_Slot_Limit_Plus_One_005c6550()) {
            limit++;
        }
    }
    for (int slot = 0; slot < 8; slot++) {
        bool beyond_map = false;
        if (slot == unknown_lobby_flag_7e6d90) {
            if (slot > Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4)) {
                NodeNameType *seated = unknown_player_slots_a3fa98[slot];
                if (seated != unknown_open_entry_a72d2c
                    && (seated == 0 || (seated != unknown_easy_ai_entry_a72d34 && seated != unknown_medium_ai_entry_a72d38
                                        && seated != unknown_hard_ai_entry_a72d3c))) {
                    beyond_map = true;
                }
            }
            if (slot == unknown_lobby_flag_7e6d90 && unknown_session_a3d29c != 0) {
                unknown_session_a3d29c->unknown_slot40();
            }
        }
        int id = Slot_Control_Id_005c97a0(slot);
        HWND combo = GetDlgItem(dialog, id);
        bool hidden = ShowWindow(combo, SW_HIDE) == 0;
        SendDlgItemMessageA(dialog, id, CB_RESETCONTENT, 0, 0);
        NodeNameType *entry = unknown_player_slots_a3fa98[slot];
        wchar_t const *text = entry->Name;
        if (entry == unknown_open_entry_a72d2c) {
            text = StringTable::Load_String("GUI:Open", 0, "D:\\Ra2\\netshare.cpp", 0x1315);
        } else if (entry == unknown_closed_entry_a72d30) {
            text = StringTable::Load_String("GUI:Closed", 0, "D:\\Ra2\\netshare.cpp", 0x1317);
        } else if (entry == unknown_easy_ai_entry_a72d34) {
            text = StringTable::Load_String("GUI:AIEasy", 0, "D:\\Ra2\\netshare.cpp", 0x1319);
        } else if (entry == unknown_medium_ai_entry_a72d38) {
            text = StringTable::Load_String("GUI:AINormal", 0, "D:\\Ra2\\netshare.cpp", 0x131b);
        } else if (entry == unknown_hard_ai_entry_a72d3c) {
            text = StringTable::Load_String("GUI:AIHard", 0, "D:\\Ra2\\netshare.cpp", 0x131d);
        } else if (entry == unknown_waiting_entry_a72d40) {
            text = StringTable::Load_String("GUI:Waiting", 0, "D:\\Ra2\\netshare.cpp", 0x131f);
        } else if (entry == unknown_player_a72d44) {
            text = StringTable::Load_String("GUI:OpenObserver", 0, "D:\\Ra2\\netshare.cpp", 0x1321);
        }
        if (entry != 0
            && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                || entry == unknown_hard_ai_entry_a72d3c)
            && !ai_allowed) {
            text = StringTable::Load_String("GUI:Open", 0, "D:\\Ra2\\netshare.cpp", 0x1328);
        }
        WideString current(text);
        if (Is_Host_005c86a0()) {
            if (entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30
                && entry != unknown_waiting_entry_a72d40 && entry != unknown_player_a72d44
                && entry != unknown_easy_ai_entry_a72d34 && entry != unknown_medium_ai_entry_a72d38
                && entry != unknown_hard_ai_entry_a72d3c) {
                Add_Combo_Entry(combo, text, entry);
            }
            if (!Is_Local_Name_005c86c0(text)) {
                if (slot < limit
                    && (!beyond_map || slot != unknown_lobby_flag_7e6d90
                        || slot < Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4))) {
                    Add_Combo_Entry(combo, StringTable::Load_String("GUI:Open", 0, "D:\\Ra2\\netshare.cpp", 0x1340), unknown_open_entry_a72d2c);
                }
                if (slot == unknown_lobby_flag_7e6d90) {
                    Add_Combo_Entry(combo, StringTable::Load_String("GUI:OpenObserver", 0, "D:\\Ra2\\netshare.cpp", 0x134a), unknown_player_a72d44);
                }
                Add_Combo_Entry(combo, StringTable::Load_String("GUI:Closed", 0, "D:\\Ra2\\netshare.cpp", 0x1351), unknown_closed_entry_a72d30);
                if (ai_allowed && !beyond_map) {
                    Add_Combo_Entry(combo, StringTable::Load_String("GUI:AIEasy", 0, "D:\\Ra2\\netshare.cpp", 0x1359), unknown_easy_ai_entry_a72d34);
                    Add_Combo_Entry(combo, StringTable::Load_String("GUI:AINormal", 0, "D:\\Ra2\\netshare.cpp", 0x135f), unknown_medium_ai_entry_a72d38);
                    Add_Combo_Entry(combo, StringTable::Load_String("GUI:AIHard", 0, "D:\\Ra2\\netshare.cpp", 0x1365), unknown_hard_ai_entry_a72d3c);
                }
            }
        } else {
            Add_Combo_Entry(combo, text, entry);
        }
        SendMessageA(combo, 0x4C0, -1, (LPARAM)current.unknown_text_770430());
        if (!hidden) {
            ShowWindow(combo, SW_SHOW);
        }
    }
}
