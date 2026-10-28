// ColorScheme *ProgressScreenClass::Text_Color_Scheme() (0x0061EE80)
// LightGrey when the local player only observes a multiplayer game (team -1),
// else the side's colours.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref ??_C@_09LBMK@LightGrey?$AA@=007ebfc4

ColorScheme *ProgressScreenClass::Text_Color_Scheme()
{
    if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_players_a3fa7c[0]->Team == -1) {
        return unknown_color_scheme_663d30("LightGrey", 1);
    }
    if (Side == 0) {
        return unknown_color_scheme_663d30("AlliedLoad", 1);
    }
    return unknown_color_scheme_663d30("SovietLoad", 1);
}
