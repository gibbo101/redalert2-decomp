// bool Slots_Filled_005c9440() (0x005C9440)
#include "shared/lobby.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?unknown_max_players_a3d558@@3HA=00a3d558
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

bool Slots_Filled_005c9440()
{
    int count = unknown_max_players_a3d558 < unknown_int_a3db1c ? unknown_max_players_a3d558 : unknown_int_a3db1c;
    for (int i = 0; i < count; i++) {
        if (unknown_player_slots_a3fa98[i] == unknown_open_entry_a72d2c) {
            return false;
        }
    }
    if (unknown_lobby_flag_7e6d90 == 0 && count < 8 && unknown_player_slots_a3fa98[count] == unknown_open_entry_a72d2c) {
        return false;
    }
    return true;
}
