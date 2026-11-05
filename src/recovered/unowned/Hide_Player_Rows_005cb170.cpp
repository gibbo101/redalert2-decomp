// Hide unused player rows, full original 005CB170..005CB300 (400 bytes).
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/multiplayer_game_mode.hpp"
void __fastcall Unknown_005cb170(HWND dialog,int first)
{
    for(int slot=first;slot<8;++slot) {
        if(slot==unknown_lobby_flag_7e6d90) continue;
        int color_id=Slot_Color_Control_Id_005ca4e0(slot);
        int slot_id=Slot_Control_Id_005c97a0(slot);
        int player_id=unknown_player_control_4d0ee0(slot);
        int side_id=Player_Side_Combo_ID_4d1350(slot);
        int shade_id=Player_Color_Combo_ID_4d1cb0(slot);
        HWND color=GetDlgItem(dialog,color_id);
        HWND entry=GetDlgItem(dialog,slot_id);
        HWND player=GetDlgItem(dialog,player_id);
        HWND side=GetDlgItem(dialog,side_id);
        HWND shade=GetDlgItem(dialog,shade_id);
        ShowWindow(color,0);
        ShowWindow(entry,0);
        ShowWindow(player,0);
        ShowWindow(side,0);
        ShowWindow(shade,0);
    }
}
