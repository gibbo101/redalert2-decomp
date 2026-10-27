// bool MultiplayerSiege::unknown_slot4() -- 0x005AB5F0 (the MultiplayerSiege unit)
// Slot 4: after the base step (0x005B7350) the first player defends (team
// 1); the loop over the rest assigns team 2 to the second entry only (as
// the original code does). False if the base step fails.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ?unknown_slot4@MultiplayerGameMode@@UAE_NXZ=005b7350
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownPlayerEntry@@@@A=00a3fa7c

bool MultiplayerSiege::unknown_slot4()
{
    if (!MultiplayerGameMode::unknown_slot4()) {
        return false;
    }
    if (unknown_players_a3fa7c.Count() > 0) {
        unknown_players_a3fa7c[0]->Team = 1;
        for (int index = 1; index < unknown_players_a3fa7c.Count(); index++) {
            unknown_players_a3fa7c[1]->Team = 2;
        }
    }
    return true;
}
