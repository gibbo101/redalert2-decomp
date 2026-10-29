// bool Unknown_005c94b0() (0x005C94B0)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

static bool Is_Seated_Entry(NodeNameType *entry)
{
    return entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30
        && entry != unknown_player_a72d44 && entry != unknown_waiting_entry_a72d40;
}

bool Unknown_005c94b0()
{
    for (int i = 0; i < 8; i++) {
        if (Is_Seated_Entry(unknown_player_slots_a3fa98[i]) && i == unknown_lobby_flag_7e6d90
            && unknown_player_slots_a3fa98[i]->Team == -1) {
            return true;
        }
    }
    return false;
}
