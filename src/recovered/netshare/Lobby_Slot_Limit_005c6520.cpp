// int Lobby_Slot_Limit_005c6520() (0x005C6520)
#include "shared/lobby.hpp"

int Lobby_Slot_Limit_005c6520()
{
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c370() && !unknown_73c3a0()) {
            return 2;
        }
        return 4;
    }
    return 8;
}
