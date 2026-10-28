// void __fastcall Set_Player_Ping_4d1060(HWND dialog, int player, int ping) (0x004D1060)
// Shows a ping image in a player row's 0x754-0x75B control.
#include "shared/gdlg_supp.hpp"
#include "shared/owner_draw_dialog_control.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref ?unknown_5e1f30@OwnerDraw@@YIXPAUHWND__@@PAVSurface@@@Z=005e1f30

void __fastcall Set_Player_Ping_4d1060(HWND dialog, int player, int ping)
{
    HWND control = GetDlgItem(dialog, unknown_player_control_4d1000(player));
    Surface *image = Ping_Image_4d0fb0(ping);
    if (control != (HWND)-1) {
        OwnerDraw::unknown_5e1f30(control, image);
    }
}
