// @ref ??_C@_0M@GKHD@wolacpt?4pcx?$AA@=007e69a0
// @ref ??_C@_0M@BDDC@wolhost?4pcx?$AA@=007e69ac
// @ref ??_C@_07LLCA@TXT_NOD?$AA@=007e69b8
// @ref ??_C@_07KDFL@TXT_GDI?$AA@=007e69c0
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref $L18554=005bc3bc
// @ref $L9801=005bc042
// @ref $L9804=005bc055
// @ref $L9805=005bc068
// @ref $L9806=005bc07e
// @ref $L9807=005bc091
// @ref $L9808=005bc0a4
// @ref $L9810=005bc0ab
// @ref $L9811=005bc0ce
// @ref $L9812=005bc0f1
#include "shared/lobby.hpp"
#include "shared/lobby_name_set.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
#include "shared/progress_screen.hpp"
namespace OwnerDraw { int __fastcall unknown_5eab00(HWND control); }
namespace seed_005c8680 { bool __fastcall FUN_005c8680(int player); }
void __fastcall Save_List_Selection_005c5ff0(HWND list,LobbyNameSet *names);
void __fastcall Restore_List_Selection_005c6310(HWND list,LobbyNameSet *names);
extern int unknown_column_a71de8;
extern int unknown_column_a71e18;
extern int unknown_column_a71e28;
extern wchar_t const unknown_empty_wide_839d4c[];
// @ref ?unknown_column_a71de8@@3HA=00a71de8
// @ref ?unknown_column_a71e18@@3HA=00a71e18
// @ref ?unknown_column_a71e28@@3HA=00a71e28
// @ref ?unknown_empty_wide_839d4c@@3PBGB=00839d4c
static bool Find_Active_Game_Dialog(HWND &active)
{
    active=Unknown_00735B10();
    int dialog_id=Current_Dialog_Id_00735b20();
    if(dialog_id==0xbc || dialog_id==0xbd) {
        return true;
    }
    active=(HWND)unknown_previous_key((int)active);
    while(active) {
        int kind=OwnerDraw::unknown_5eab00(active);
        if(kind==0xbc || kind==0xbd) {
            return true;
        }
        active=(HWND)unknown_previous_key((int)active);
    }
    return false;
}

// Rebuild the LAN chat or game roster while preserving selection and scroll.
void __fastcall Unknown_005bbdd0(bool full)
{
    HWND active;
    if(Find_Active_Game_Dialog(active)) {
        Refresh_Slot_Settings_005ca000(active,full);
        return;
    }
    {
    HWND dialog=Unknown_00735B10();
    HWND list=GetDlgItem(dialog,0x53e);
    if(dialog && list) {
        HWND users=GetDlgItem(dialog,0x53e);
        WolLadderListCell cell;
        int top=SendDlgItemMessageA(dialog,0x53e,0x18e,0,0);
        SendDlgItemMessageA(dialog,0x53e,0x49d,0,1);
        LobbyNameSet selections(Hash_Wide_Name_005c2bf0);
        Save_List_Selection_005c5ff0(list,&selections);
        SendDlgItemMessageA(dialog,0x53e,0x184,0,0);
        if(unknown_game_index_a71e90==0) {
            SendMessageA(users,0x4cc,0,(LPARAM)Unknown_006FA180(unknown_name_a3d3a0));
            for(int chat=1;chat<unknown_chat_a3fa4c.Count();++chat)
                SendMessageA(users,0x4cc,chat,(LPARAM)unknown_chat_a3fa4c[chat]);
        } else {
            for(int player=0;player<unknown_players_a3fa7c.Count();++player) {
                int state=0;
                if(seed_005c8680::FUN_005c8680(player)) {
                    state=2;
                    unknown_players_a3fa7c[player]->unknown_67=1;
                } else if(unknown_players_a3fa7c[player]->unknown_67!=0) state=1;
                wchar_t info[128];
                wchar_t country_name[128];
                swprintf(info,L"%s",unknown_players_a3fa7c[player]);
                int country=unknown_players_a3fa7c[player]->unknown_66e290();
                Surface *flag=Country_Flag_004d1120(country);
                switch(country) {
                case 0: swprintf(country_name,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\netdlg2.cpp",383)); break;
                case 1: swprintf(country_name,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\netdlg2.cpp",386)); break;
                case 2: swprintf(country_name,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\netdlg2.cpp",389)); break;
                case 3: swprintf(country_name,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\netdlg2.cpp",392)); break;
                case 4: swprintf(country_name,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\netdlg2.cpp",395)); break;
                case 5: swprintf(country_name,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\netdlg2.cpp",398)); break;
                case 6: swprintf(country_name,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\netdlg2.cpp",401)); break;
                case 7: swprintf(country_name,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\netdlg2.cpp",404)); break;
                case 8: swprintf(country_name,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\netdlg2.cpp",407)); break;
                }
                SendMessageA(users,0x4cc,-1,(LPARAM)info);
                int color=unknown_color_values_7e6d94[unknown_players_a3fa7c[player]->unknown_53];
                cell.Flags=4;
                cell.unknown_0c=color;
                cell.Secondary.Set(unknown_empty_wide_839d4c);
                SendDlgItemMessageA(dialog,0x53e,0x4a8,(unsigned short)unknown_column_a71de8|((unsigned long)(unsigned short)player<<16),(LPARAM)&cell);
                cell.Flags=2;
                cell.Secondary.Set(country_name);
                cell.unknown_10=(int)flag;
                SendDlgItemMessageA(dialog,0x53e,0x4a8,(unsigned short)unknown_column_a71e18|((unsigned long)(unsigned short)player<<16),(LPARAM)&cell);
                cell.Secondary.Set(unknown_empty_wide_839d4c);
                cell.Flags=2;
                if(state==2) cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolhost.pcx",0);
                else if(state) cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolacpt.pcx",0);
                else cell.Flags=0;
                SendDlgItemMessageA(dialog,0x53e,0x4a8,(unsigned short)unknown_column_a71e28|((unsigned long)(unsigned short)player<<16),(LPARAM)&cell);
            }
        }
        Restore_List_Selection_005c6310(list,&selections);
        SendDlgItemMessageA(dialog,0x53e,0x197,top,0);
        SendDlgItemMessageA(dialog,0x53e,0x49d,0,0);
        InvalidateRect(list,0,0);
        UpdateWindow(list);
    }
    }
    return;

}
