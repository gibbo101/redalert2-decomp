// void __fastcall Unknown_005cd030(HWND dialog, bool value) (0x005CD030)
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Unknown_005cd030(HWND dialog, bool value)
{
    if (dialog != 0) {
        int slot = Find_First_Player_Slot_005c8c70();
        if (slot != unknown_lobby_flag_7e6d90) {
            HWND control = GetDlgItem(dialog, Player_Side_Combo_ID_4d1350(slot));
            if (control != 0) {
                EnableWindow(control, value);
            }
            control = GetDlgItem(dialog, Player_Color_Combo_ID_4d1cb0(slot));
            if (control != 0) {
                EnableWindow(control, value);
            }
        }
    }
}
