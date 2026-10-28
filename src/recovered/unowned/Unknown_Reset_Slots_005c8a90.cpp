// void Unknown_Reset_Slots_005c8a90() (0x005C8A90)
// Resets the lobby's player slots: the first 2, 4 or 8 (by game mode and the
// network tests) get the first fixed entry, the rest the second; the slot
// before the table is set to -1, the lobby state is told and two words clear.
#include "shared/lobby.hpp"
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUNodeNameType@@A=00a72d2c
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_lobby_a3fa94@@3HA=00a3fa94
// @ref ?unknown_lobby_a728e4@@3GA=00a728e4
// @ref ?unknown_lobby_a72734@@3GA=00a72734
// @ref ?unknown_lobby_state_a3d2b0@@3VUnknownLobbyState@@A=00a3d2b0
// @ref ?Unknown_00672810@UnknownLobbyState@@QAEXXZ=00672810
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_73c370@@YA_NXZ=0073c370
// @ref ?unknown_73c3a0@@YA_NXZ=0073c3a0

void Unknown_Reset_Slots_005c8a90()
{
    int limit;
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c370() && !unknown_73c3a0()) {
            limit = 2;
        } else {
            limit = 4;
        }
    } else {
        limit = 8;
    }
    for (int i = 0; i < limit; i++) {
        unknown_player_slots_a3fa98[i] = unknown_lobby_entries_a72d2c[0];
    }
    for (int j = limit; j < 8; j++) {
        unknown_player_slots_a3fa98[j] = unknown_lobby_entries_a72d2c[1];
    }
    unknown_lobby_a3fa94 = -1;
    unknown_lobby_state_a3d2b0.Unknown_00672810();
    unknown_lobby_a728e4 = 0;
    unknown_lobby_a72734 = 0;
}
