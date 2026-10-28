// void __fastcall Fill_Side_Combos_4d16d0(HWND dialog) (0x004D16D0)
// Refills every player row's side combo box: a row whose player combo box
// (control id = the row) holds the 0x00A72D44 entry gets the observer entry
// alone, the others the countries.
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_combo_selected_data_005c99d0@@YIHPAUHWND__@@HH@Z=005c99d0
// @ref ?Fill_Side_Combo_4d1560@@YIXPAUHWND__@@H@Z=004d1560

void __fastcall Fill_Side_Combos_4d16d0(HWND dialog)
{
    for (int player = 0; player < 8; player++) {
        int data = unknown_combo_selected_data_005c99d0(dialog, player, -1);
        bool observer = false;
        if (unknown_player_a72d44 != 0 && data == (int)unknown_player_a72d44) {
            observer = true;
        }
        int id = Player_Side_Combo_ID_4d1350(player);
        if (observer) {
            Fill_Observer_Combo_4d1640(dialog, id);
        } else {
            Fill_Side_Combo_4d1560(dialog, id);
        }
    }
}
