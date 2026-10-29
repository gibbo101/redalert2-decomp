// void __fastcall Select_Player_Side_4d1820(HWND dialog, int player) (0x004D1820)
// Selects the session player's country in a row's side combo box (random,
// -2, or observer, -3, when the session says so).
#include "shared/gdlg_supp.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298

void __fastcall Select_Player_Side_4d1820(HWND dialog, int player)
{
    int side = unknown_session_a3d298.unknown_134;
    if (unknown_session_a3d298.unknown_138 == -2) {
        side = -2;
    } else if (unknown_session_a3d298.unknown_138 == -3) {
        side = -3;
    }
    Select_Side_Combo_4d1a90(dialog, Player_Side_Combo_ID_4d1350(player), side);
}
