// int Lobby_Slot_Limit_Plus_One_005c6550() (0x005C6550)
#include "shared/lobby.hpp"

int Lobby_Slot_Limit_Plus_One_005c6550()
{
    int limit = Lobby_Slot_Limit_005c6520();
    if (unknown_game_mode_a3d298 == 4) {
        if (limit >= 4) {
            return limit;
        }
    } else if (limit >= 8) {
        return limit;
    }
    return limit + 1;
}
