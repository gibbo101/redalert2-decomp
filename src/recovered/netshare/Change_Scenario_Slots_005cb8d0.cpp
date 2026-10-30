// void __fastcall Change_Scenario_Slots_005cb8d0(HWND dialog, int previous, int scenario) (0x005CB8D0)
// Adapts the slot combos to a new scenario: its player count (limited to the lobby's slot limit when
// computer players are not allowed) against the previous count opens the added slots or closes the removed
// ones, an extra open slot is kept when the lobby allows one more; previous -1 resets the counts and the
// host's observer combo. Afterwards the observer slots are redone and, when the mode wants slot 7 as the
// observer slot, the host announces it. The counts are kept for the next call.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/debug_printf.hpp"
#include "shared/wide_string.hpp"
#include "shared/crt_string.hpp"
// @ref ?Unknown_005cb560@@YIXPAUHWND__@@@Z=005cb560
// @ref ?unknown_extra_slot_a72d5c@@3HA=00a72d5c
// @ref ?unknown_slot_count_7e6de4@@3HA=007e6de4
// @ref ??_C@_05MFEC@O?$CFd?$CFs?$AA@=007e73b0
// @ref ??_C@_0BM@HEHH@Sending?5observer?5slot?5of?57?6?$AA@=007e73b8

void __fastcall Change_Scenario_Slots_005cb8d0(HWND dialog, int previous, int scenario)
{
    int players = Scenario_Slot_Limit_005c65a0(scenario);
    bool ai_allowed = (unknown_session_a3d29c == 0 || unknown_session_a3d29c->unknown_slot12()) && !unknown_73c370();
    if (!ai_allowed) {
        int limit = Lobby_Slot_Limit_005c6520();
        if (players > limit) {
            players = limit;
        }
    }
    if (previous == -1) {
        unknown_slot_count_7e6de4 = 8;
        unknown_extra_slot_a72d5c = 0;
    }
    int added = players - unknown_slot_count_7e6de4;
    int extra = 0;
    if (unknown_lobby_flag_7e6d90 == 0) {
        if (ai_allowed || players < Lobby_Slot_Limit_Plus_One_005c6550()) {
            extra = 1;
            if (unknown_extra_slot_a72d5c == 0 && added + players < 7) {
                added++;
            }
        }
    }
    if (previous == -1 && unknown_lobby_flag_7e6d90 == 0) {
        int side = Player_Side_Combo_ID_4d1350(0);
        Fill_Observer_Combo_4d1640(dialog, side);
        Select_Side_Combo_4d1a90(dialog, side, -3);
        SendMessageA(GetDlgItem(dialog, 0x411), 0x4F1, 0, 1);
        int color = Player_Color_Combo_ID_4d1cb0(0);
        Fill_Random_Color_Combo_4d2250(dialog, color);
        Select_Color_Combo_4d2480(dialog, color, 8);
    }
    if (added > 0) {
        Unknown_005cb3f0(dialog, unknown_extra_slot_a72d5c + unknown_slot_count_7e6de4, added);
    } else if (added < 0) {
        int first = extra + players;
        int limit = Lobby_Slot_Limit_005c6520();
        for (int slot = first; slot < 8; slot++) {
            int id = Slot_Control_Id_005c97a0(slot);
            if (slot < limit) {
                if (slot != unknown_lobby_flag_7e6d90) {
                    Unknown_005cbf20(dialog, id, unknown_open_entry_a72d2c, 1);
                }
            } else if (slot != unknown_lobby_flag_7e6d90) {
                Unknown_005cbf20(dialog, id, unknown_closed_entry_a72d30, 1);
            }
        }
        Unknown_005cb170(dialog, first);
        if (unknown_chat_a72cfc != 0) {
            unknown_call_73fee0_default();
        } else {
            Unknown_005bbdc0();
        }
        Unknown_005c3810(true, false);
    } else if (extra + players >= 7) {
        Unknown_005cb3f0(dialog, 7, 1);
    }
    Unknown_005cb560(dialog);
    if (unknown_lobby_flag_7e6d90 == -1 && unknown_session_a3d29c != 0 && unknown_session_a3d29c->unknown_slot40()) {
        unknown_lobby_flag_7e6d90 = 7;
        Unknown_005cb560(dialog);
        Debug_Printf("Sending observer slot of 7\n");
        char text[0x100];
        NodeNameType *entry = unknown_player_slots_a3fa98[unknown_lobby_flag_7e6d90];
        WideString name;
        if (entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30
            && entry != unknown_waiting_entry_a72d40 && entry != unknown_player_a72d44
            && entry != unknown_easy_ai_entry_a72d34 && entry != unknown_medium_ai_entry_a72d38
            && entry != unknown_hard_ai_entry_a72d3c) {
            name = entry->Name;
        } else {
            Wstring narrow = Unknown_Lobby_Entry_Name_005cd0e0(entry);
            name = Wstring_To_Wide(narrow);
        }
        {
            WideString wide(name.Get());
            sprintf(text, "O%d%s", unknown_lobby_flag_7e6d90, Narrow_Copy_00771280(wide).Buffer);
        }
        Send_Game_Options_005c3c60(text);
    }
    unknown_slot_count_7e6de4 = players;
    unknown_extra_slot_a72d5c = extra;
}
