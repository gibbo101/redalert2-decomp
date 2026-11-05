// Show player rows, full original005CAE00 body450+14 frozen padding.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
void __fastcall Unknown_005cae00(HWND dialog,int first,int count)
{
    int end=first+count;
    for(int slot=first;slot<end;++slot) {
        int color_id=Slot_Color_Control_Id_005ca4e0(slot);
        int slot_id=Slot_Control_Id_005c97a0(slot);
        int player_id=unknown_player_control_4d0ee0(slot);
        int shade_id=Player_Color_Combo_ID_4d1cb0(slot);
        int side_id=Player_Side_Combo_ID_4d1350(slot);
        HWND color=GetDlgItem(dialog,color_id);
        HWND combo=GetDlgItem(dialog,slot_id);
        HWND player=GetDlgItem(dialog,player_id);
        HWND shade=GetDlgItem(dialog,shade_id);
        HWND side=GetDlgItem(dialog,side_id);
        NodeNameType *entry=unknown_player_slots_a3fa98[slot];
        bool observer;
        if(entry==unknown_player_a72d44 || (entry!=0 && entry!=unknown_open_entry_a72d2c && entry!=unknown_closed_entry_a72d30 && entry!=unknown_waiting_entry_a72d40 && entry->Team==-1)) observer=true;
        else observer=false;
        ShowWindow(color,5);
        ShowWindow(combo,5);
        ShowWindow(player,5);
        if(observer) ShowWindow(shade,0);
        else ShowWindow(shade,5);
        ShowWindow(side,5);
    }
}
