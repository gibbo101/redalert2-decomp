// void __fastcall Select_Player_Color_4d23c0(HWND dialog, int player) (0x004D23C0)
// Selects the session player's colour in a row's colour combo box: random
// (-2) with a random country; in game modes 3 and 4 the observer colour (8)
// for the 0x00A72D44 entry without a team.
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44


void __fastcall Select_Player_Color_4d23c0(HWND dialog, int player)
{
    int color = unknown_session_a3d298.unknown_12c;
    if (unknown_session_a3d298.unknown_130 == -2) {
        color = -2;
    }
    int id = Player_Color_Combo_ID_4d1cb0(player);
    if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4)
        && unknown_player_slots_a3fa98[player] == unknown_player_a72d44 && unknown_player_slots_a3fa98[player]->Team == -1) {
        color = 8;
    }
    Select_Color_Combo_4d2480(dialog, id, color);
}
