// void MPCooperative::unknown_player_colors_5a3920() -- 0x005A3920
// The session colours (0x00A71118, eight): -2 (none), then each session player's colour by its index.
// No entry references: slot 21 0x005A3960 expands it.
// @ref ?Get_Color_0066e2b0@NodeNameType@@QAEHXZ=0066e2b0
// @ref ?unknown_colors_a71118@@3PAHA=00a71118
#include "shared/multiplayer_game_mode.hpp"

void MPCooperative::unknown_player_colors_5a3920()
{
    int i;
    for (i = 0; i < 8; i++) {
        unknown_colors_a71118[i] = -2;
    }
    int count = unknown_players_a3fa7c.Count();
    for (i = 0; i < count; i++) {
        unknown_colors_a71118[i] = unknown_players_a3fa7c[i]->Get_Color_0066e2b0();
    }
}
