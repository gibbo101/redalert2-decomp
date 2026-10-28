// void __fastcall Fill_Color_Combos_4d2300(HWND dialog) (0x004D2300)
// Refills every player row's colour combo box; in game modes 3 and 4 a row
// with the 0x00A72D44 entry or without a team gets the random entry alone.
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?Fill_Color_Combo_4d2080@@YIXPAUHWND__@@H@Z=004d2080

void __fastcall Fill_Color_Combos_4d2300(HWND dialog)
{
    for (int player = 0; player < 8; player++) {
        int id = Player_Color_Combo_ID_4d1cb0(player);
        if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4)
            && (unknown_player_slots_a3fa98[player] == unknown_player_a72d44 || unknown_player_slots_a3fa98[player]->Team == -1)) {
            Fill_Random_Color_Combo_4d2250(dialog, id);
        } else {
            Fill_Color_Combo_4d2080(dialog, id);
        }
    }
}
