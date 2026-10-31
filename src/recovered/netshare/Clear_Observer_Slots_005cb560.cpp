// void __fastcall Clear_Observer_Slots_005cb560(HWND dialog) (0x005CB560)
// Without an observer slot (unknown_lobby_flag_7e6d90 below 1) every slot but the first that holds the observer
// entry or an observer player (Team -1) becomes open within the slot limit and closed beyond. With one, that
// slot becomes closed when the map has fewer slots and it holds a seated non-observer player, a computer or
// the open entry; its row is shown and refilled either way. Then the colours are redone after a change, the
// LAN lobby is refreshed and the lobby state sent.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
// @ref ?Unknown_005bbdc0@@YIXXZ=005bbdc0

void __fastcall Clear_Observer_Slots_005cb560(HWND dialog)
{
    bool changed = false;
    if (unknown_lobby_flag_7e6d90 < 1) {
        int limit = Lobby_Slot_Limit_005c6520();
        for (int slot = 1; slot < 8; slot++) {
            int id = Slot_Control_Id_005c97a0(slot);
            NodeNameType *entry = unknown_player_slots_a3fa98[slot];
            if (slot < limit) {
                if (entry == unknown_player_a72d44 || entry->Team == -1) {
                    Unknown_005cbf20(dialog, id, unknown_open_entry_a72d2c, 1);
                    changed = true;
                }
            } else if (entry == unknown_player_a72d44 || entry->Team == -1) {
                Unknown_005cbf20(dialog, id, unknown_closed_entry_a72d30, 1);
                changed = true;
            }
        }
    } else {
        NodeNameType *entry = unknown_player_slots_a3fa98[unknown_lobby_flag_7e6d90];
        if (unknown_lobby_flag_7e6d90 > Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4)) {
            if ((Is_Seated_Entry(entry) && entry->Team != -1)
                || (entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                                   || entry == unknown_hard_ai_entry_a72d3c))
                || entry == unknown_open_entry_a72d2c) {
                entry = unknown_closed_entry_a72d30;
                changed = true;
            }
        }
        Unknown_005cafd0(dialog);
        Unknown_005cbf20(dialog, Slot_Control_Id_005c97a0(unknown_lobby_flag_7e6d90), entry, 1);
    }
    if (changed) {
        Set_Slot_Country_005c9a10(dialog, Player_Side_Combo_ID_4d1350(unknown_lobby_flag_7e6d90));
    }
    Unknown_005bbdc0();
    Unknown_005c3810(true, false);
}
