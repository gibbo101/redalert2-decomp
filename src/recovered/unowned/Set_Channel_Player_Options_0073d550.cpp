#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_player_entry.hpp"
int __fastcall Set_Channel_Player_Options_0073d550(Wstring const &name,int country,int color)
{
    int found=-1;
    Wstring lower=name.As_Lower();
    for(int index=0;index<8;++index) {
        Wstring player_name=Narrow_Copy_00771280(unknown_player_slots_a3fa98[index]->Name);
        if(lower==player_name.As_Lower()) {
            found=index;
            break;
        }
    }
    int changed=0;
    if(found==-1) return changed;
    HWND window=(HWND)Unknown_00735940(0xc2);
    if(!window) window=(HWND)Unknown_00735940(0xc9);
    NodeNameType *player=unknown_player_slots_a3fa98[found];
    if(player->unknown_66e290()!=country) {
        changed=1;
        player->unknown_66e2d0(country);
        int side=Player_Side_Combo_ID_4d1350(found);
        int previous=Side_Combo_Data_4d1c70(window,side,-1);
        if(country==-3) {
            if(previous!=-3) {
                Fill_Observer_Combo_4d1640(window,side);
                int observer_control=Slot_Control_Id_005c97a0(found);
                SendMessageA(GetDlgItem(window,observer_control),0x4f1,0,1);
                int color_control=Player_Color_Combo_ID_4d1cb0(found);
                Fill_Random_Color_Combo_4d2250(window,color_control);
                Select_Color_Combo_4d2480(window,color_control,8);
            }
        } else if(previous==-3) {
            Fill_Side_Combo_4d1560(window,side);
            int observer_control=Slot_Control_Id_005c97a0(found);
            SendMessageA(GetDlgItem(window,observer_control),0x4f1,0,0);
            int color_control=Player_Color_Combo_ID_4d1cb0(found);
            Fill_Color_Combo_4d2080(window,color_control);
            Select_Color_Combo_4d2480(window,color_control,-2);
        }
        if(player->unknown_66e290()==-3) player->Team=-1;
    }
    if(unknown_player_slots_a3fa98[found]->unknown_66e2a0()!=color) player->unknown_66e300(color);
    if(unknown_player_slots_a3fa98[found]==unknown_players_a3fa7c[0]) unknown_a3d3b4=color;
    Unknown_0073FEE0(0,false);
    return changed;
}
