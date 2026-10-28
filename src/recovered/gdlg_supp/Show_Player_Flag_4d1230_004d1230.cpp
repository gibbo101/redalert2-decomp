// void __fastcall Show_Player_Flag_4d1230(HWND dialog, int player) (0x004D1230)
// Shows the flag of the country selected in a player row's side combo box in
// the row's 0x6DA-0x6E1 control.
#include "shared/gdlg_supp.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/progress_screen.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref ?unknown_5e1f30@OwnerDraw@@YIXPAUHWND__@@PAVSurface@@@Z=005e1f30

void __fastcall Show_Player_Flag_4d1230(HWND dialog, int player)
{
    HWND control = GetDlgItem(dialog, unknown_player_control_4d0ee0(player));
    OwnerDraw::unknown_5e1f30(control, Country_Flag_004d1120(Side_Combo_Data_4d1c70(dialog, Player_Side_Combo_ID_4d1350(player), -1)));
}
