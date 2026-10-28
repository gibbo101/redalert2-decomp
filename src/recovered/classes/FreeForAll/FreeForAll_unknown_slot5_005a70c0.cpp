// bool FreeForAll::unknown_slot5(WideString *message) -- 0x005A70C0
// Slot 5 (the team check before a game): after the base check (0x005B73A0), every player
// with a team (not -1) gets a team of its own (its index in the session list).
// @ref ?unknown_slot5@MultiplayerGameMode@@UAE_NPAVWideString@@@Z=005b73a0
#include "shared/multiplayer_game_mode.hpp"

bool FreeForAll::unknown_slot5(WideString *message)
{
    if (!MultiplayerGameMode::unknown_slot5(message)) {
        return false;
    }
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        NodeNameType *node = unknown_players_a3fa7c[index];
        if (node->Team != -1) {
            unknown_players_a3fa7c[index]->Team = index;
        }
    }
    return true;
}
