// int __fastcall Slot_Country_005ca3f0(int slot) (0x005CA3F0)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

int __fastcall Slot_Country_005ca3f0(int slot)
{
    int country = -2;
    NodeNameType *entry = unknown_player_slots_a3fa98[slot];
    if (unknown_session_a3d29c != 0 && (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4)) {
        country = unknown_session_a3d29c->unknown_slot10();
    }
    if (entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                       || entry == unknown_hard_ai_entry_a72d3c)) {
        return unknown_lobby_a3d2fc[slot];
    }
    if (entry == unknown_open_entry_a72d2c || entry == unknown_closed_entry_a72d30
        || entry == unknown_waiting_entry_a72d40) {
        return country;
    }
    if (entry == unknown_player_a72d44) {
        return -3;
    }
    return entry->unknown_66e290();
}
