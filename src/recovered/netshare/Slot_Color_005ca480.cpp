// int __fastcall Slot_Color_005ca480(int slot) (0x005CA480)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

int __fastcall Slot_Color_005ca480(int slot)
{
    NodeNameType *entry = unknown_player_slots_a3fa98[slot];
    if (entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                       || entry == unknown_hard_ai_entry_a72d3c)) {
        return unknown_lobby_a3d31c[slot];
    }
    if (entry == unknown_open_entry_a72d2c) {
        return -2;
    }
    if (entry == unknown_closed_entry_a72d30) {
        return -2;
    }
    if (entry == unknown_waiting_entry_a72d40) {
        return -2;
    }
    if (entry == unknown_player_a72d44) {
        return -2;
    }
    return entry->Get_Color_0066e2a0();
}
