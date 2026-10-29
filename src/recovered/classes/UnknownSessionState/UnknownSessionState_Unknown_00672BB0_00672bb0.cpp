#include "shared/multiplayer_game_mode.hpp"

// Resolves the random countries and colours (see the declaration); 0x00672940 and 0x00672980 are expanded on the
// global session.
void UnknownSessionState::Unknown_00672BB0()
{
    int count = unknown_players_a3fa7c.Count();
    int i;
    for (i = 0; i < count; i++) {
        NodeNameType *player = unknown_players_a3fa7c[i];
        if (player->unknown_4f == -3 || player->unknown_4b == -3) {
            player->unknown_4b = -3;
            player->unknown_4f = -1;
            player->unknown_53 = 8;
            player->unknown_57 = -1;
        } else {
            if (player->unknown_4f == -2) {
                player->unknown_4f = -1;
                if (Mode) {
                    player->unknown_4b = Mode->unknown_slot23();
                } else {
                    player->unknown_4b = unknown_session_a3d298.Unknown_00672940();
                }
            }
            if (player->unknown_57 == -2) {
                player->unknown_57 = -1;
                player->unknown_53 = -1;
                player->unknown_53 = unknown_session_a3d298.Unknown_00672980();
            }
        }
        if (i == 0) {
            unknown_a3d3b4 = player->unknown_53;
        }
    }
    for (i = 0; i < 8; i++) {
        if (unknown_session_a3d298.AICountry[i] == -2) {
            if (Mode) {
                unknown_session_a3d298.AICountry[i] = Mode->unknown_slot24();
            } else {
                unknown_session_a3d298.AICountry[i] = unknown_session_a3d298.Unknown_00672940();
            }
        }
        if (unknown_session_a3d298.AIColor[i] == -2) {
            unknown_session_a3d298.AIColor[i] = unknown_session_a3d298.Unknown_00672980();
        }
    }
}
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
