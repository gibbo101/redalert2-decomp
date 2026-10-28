// ColorScheme *ProgressScreenClass::Player_Color_Scheme(int player) (0x0061EED0)
// A player's colours (an observer's are those of colour -2); null for an
// index past the eight players.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/color_scheme.hpp"
// @ref ?Get_Color_0066e2a0@NodeNameType@@QAEHXZ=0066e2a0

ColorScheme *ProgressScreenClass::Player_Color_Scheme(int player)
{
    ColorScheme *scheme = 0;
    if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
        int team = unknown_players_a3fa7c[player]->Team;
        if (team == -1) {
            int index = unknown_session_a3d298.Unknown_006715D0(-2);
            scheme = ColorSchemes[index];
            return scheme;
        }
    }
    if (player >= 0 && player < 8) {
        int color = unknown_players_a3fa7c[player]->Get_Color_0066e2a0();
        int index = unknown_session_a3d298.Unknown_006715D0(color);
        scheme = ColorSchemes[index];
    }
    return scheme;
}
