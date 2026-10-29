// void Fill_Slots_005c8a10() (0x005C8A10)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

void Fill_Slots_005c8a10()
{
    int limit = Lobby_Slot_Limit_005c6520();
    for (int i = 0; i < limit; i++) {
        unknown_player_slots_a3fa98[i] = unknown_open_entry_a72d2c;
    }
    for (int j = limit; j < 8; j++) {
        unknown_player_slots_a3fa98[j] = unknown_closed_entry_a72d30;
    }
}
