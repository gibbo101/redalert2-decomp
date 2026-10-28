// void MPCooperative::unknown_slot33() -- 0x005A4F90
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?unknown_text_839d4c@@3PADA=00839d4c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
void MPCooperative::unknown_slot33()
{
    HWND dialog = Get_Lobby_Dialog_005c2c40();
    if (dialog != 0) {
        HWND item = GetDlgItem(dialog, 0x72F);
        if (item != 0) {
            SendMessageA(item, 0x4B2, 0, (LPARAM)unknown_text_839d4c);
            ShowWindow(item, SW_HIDE);
        }
        Fill_Side_Combos_4d16d0(dialog);
    }
    for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
        unknown_players_a3fa7c[i]->Team = i;
    }
}
