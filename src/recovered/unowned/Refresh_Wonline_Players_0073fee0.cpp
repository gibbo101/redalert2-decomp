// 0073FEE0: complete Wonline player-list refresh, independent original bounds5132+4NOP.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/lobby_name_set.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/house_type.hpp"
#include "shared/pcx_cache.hpp"
void __fastcall Unknown_005c5ff0(HWND list,LobbyNameSet *selection);
void __fastcall Restore_List_Selection_005c6310(HWND list,LobbyNameSet *selection);
WideString __fastcall Locale_Name_0073f1c0(int locale);
extern "C" int __cdecl tolower(int character);
// @ref ?Unknown_005c5ff0@@YIXPAUHWND__@@PAVLobbyNameSet@@@Z=005c5ff0
// @ref ?Restore_List_Selection_005c6310@@YIXPAUHWND__@@PAVLobbyNameSet@@@Z=005c6310
// @ref ?Locale_Name_0073f1c0@@YI?AVWideString@@H@Z=0073f1c0
// @ref _tolower=007841f4
extern int player_list_colors_007e6d94[];
// @ref ?player_list_colors_007e6d94@@3PAHA=007e6d94
extern wchar_t player_list_locale_00b29738[64];
// @ref ?player_list_locale_00b29738@@3PAGA=00b29738
extern wchar_t player_list_w_00839d4c[];
// @ref ?player_list_w_00839d4c@@3PAGA=00839d4c
extern int player_list_column_00b2a81c;
// @ref ?player_list_column_00b2a81c@@3HA=00b2a81c
extern int player_list_column_00b292a4;
// @ref ?player_list_column_00b292a4@@3HA=00b292a4
extern int player_list_column_00b2657c;
// @ref ?player_list_column_00b2657c@@3HA=00b2657c
extern int player_list_column_00b2ab80;
// @ref ?player_list_column_00b2ab80@@3HA=00b2ab80
extern int player_list_column_00b292e0;
// @ref ?player_list_column_00b292e0@@3HA=00b292e0
extern int player_list_column_00b297b8;
// @ref ?player_list_column_00b297b8@@3HA=00b297b8
extern int player_list_column_00b26958;
// @ref ?player_list_column_00b26958@@3HA=00b26958

void __fastcall Unknown_0073FEE0(int keep_selection,bool full)
{
    HWND lobby=Find_Lobby_Window_005c2c40();
    if(lobby) { Refresh_Slot_Settings_005ca000(lobby,full); return; }
    if(Unknown_00735940(0x6b)) return;
    HWND window=(HWND)Unknown_00735940(0x116);
    if(window) Unknown_00755180(window);
    else window=(HWND)Unknown_00735940(0x113);
    HWND list=GetDlgItem(window,0x53e);
    if(!window || !list) return;
    LobbyNameSet selections;
    Unknown_005c5ff0(list,&selections);
    int top=SendDlgItemMessageA(window,0x53e,0x18e,0,0);
    SendDlgItemMessageA(window,0x53e,0x49d,0,1);
    SendDlgItemMessageA(window,0x53e,0x184,0,0);
    Wstring name;
    WOL::Ladder ladder;
    memset(&ladder,0,sizeof(ladder));
    WolLadderListCell cell;
    Wstring local_name=unknown_wstring_b26cb8.As_Lower();
    wchar_t info[80],rank[80];
    char count_text[20];
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        WOL::User user;
        unknown_users_b2a728.Get_Copy(user,i);
        Wstring user_name(user.name);
        if(local_name==user_name.As_Lower()) {
            HWND control=GetDlgItem(window,0x555);
            if(control) {
                LONG style=GetWindowLongA(control,-16);
                if(user.flags & 1) style &= ~0x08000000;
                else style |= 0x08000000;
                SetWindowLongA(control,-16,style);
                InvalidateRect(control,0,0);
            }
            control=GetDlgItem(window,0x587);
            if(control) {
                LONG style=GetWindowLongA(control,-16);
                if(user.flags & 1) style &= ~0x08000000;
                else style |= 0x08000000;
                SetWindowLongA(control,-16,style);
                InvalidateRect(control,0,0);
            }
        }
        if(!unknown_b299c0) {
            swprintf(info,L"%hs",user.name);
            int row=SendDlgItemMessageA(window,0x53e,0x4cc,-1,(LPARAM)info);
            cell.Flags=1;
            cell.Secondary.Set(StringTable::Load_String("TXT_UNRANKED",0,"D:\\Ra2\\wonline.cpp",0xc18));
            Unknown_006FA0C0(info,user.name,-1);
            cell.Text.Set(info);
            if(unknown_game_mode_a3d298==4 && unknown_a3d2a4==2) {
                if(!(user.flags & 1)) {
                    Wstring team_name=Narrow_Copy_00771280(cell.Text.Get());
                    if(unknown_known_names_b294b8.Contains(team_name)) {
                        int color;
                        int *value=0;
                        if(unknown_known_names_b294b8.Get_Pointer(team_name,&value) && value) color=*value;
                        WideString converted_team(Unknown_006FA180(team_name.Get()));
                        cell.Text=converted_team;
                        cell.unknown_0c=player_list_colors_007e6d94[color];
                    } else cell.unknown_0c=unknown_color_7a7360;
                } else cell.unknown_0c=unknown_color_7a7360;
            } else cell.unknown_0c=unknown_color_7a7360;
            name.Set(user.name);
            name.To_Lower();
            memset(player_list_locale_00b29738,0,sizeof(player_list_locale_00b29738));
            int locale=0;
            if(unknown_channel_names_b293a0.Contains(name) && unknown_chat_a72cfc) {
                int *value=0;
                if(unknown_channel_names_b293a0.Get_Pointer(name,&value) && value) locale=*value;
                if(locale) {
                    WideString locale_name=Locale_Name_0073f1c0(locale);
                    swprintf(player_list_locale_00b29738,L"(%hs)",locale_name.Get());
                }
            }
            if(unknown_ladder_cache_b2ac24->Get_Copy(ladder,name)) {
                swprintf(rank,L"%s %d",StringTable::Load_String("TXT_RANK",0,"D:\\Ra2\\wonline.cpp",0xc5a),ladder.unknown_1c);
                cell.Secondary.Set(rank);
            }
            if(unknown_channel_names_b293a0.Contains(name)) {
                if(locale) cell.Secondary.Insert(L" ",0);
                cell.Secondary.Insert(player_list_locale_00b29738,0);
            }
            SendMessageA(GetDlgItem(window,0x53e),0x19a,row,i);
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b2a81c | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            cell.Flags=1;
            name.Set(user.name);
            name.To_Lower();
            rank[0]=0;
            if(strlen(user.unknown_57)) {
                swprintf(rank,L"[%hs]",user.unknown_57);
                wchar_t squad_name[200];
                Unknown_006FA0C0(squad_name,user.unknown_2e,-1);
                cell.Secondary.Set(squad_name);
            } else if(unknown_ladder_cache_b2ac24->Get_Copy(ladder,name)) {
                swprintf(rank,L"(%s %d)",StringTable::Load_String("TXT_RANK",0,"D:\\Ra2\\wonline.cpp",0xc84),ladder.unknown_1c);
                cell.Secondary.Set(player_list_w_00839d4c);
            }
            cell.Text.Set(rank);
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b292a4 | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            cell.Flags=1;
            if(user.flags & 1) {
                cell.Flags=2;
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("woloper.pcx",0);
                cell.Secondary.Set(StringTable::Load_String("TXT_OPER",0,"D:\\Ra2\\wonline.cpp",0xc90));
            } else if(user.flags & 2) {
                cell.Flags=2;
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolvoice.pcx",0);
                cell.Secondary.Set(StringTable::Load_String("TXT_VOICE",0,"D:\\Ra2\\wonline.cpp",0xc96));
            } else {
                cell.Text.Set(player_list_w_00839d4c);
                cell.Secondary.Set(player_list_w_00839d4c);
            }
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b2657c | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
        } else {
            if(HouseTypes.Count()<=1) return;
            int index;
            { Wstring lookup_name(user.name); index=unknown_users_b2a728.Find_Name(lookup_name); }
            int country=0,star=0;
            if(index!=-1) {
                country=unknown_player_b29cf0[index].unknown_18;
                if(unknown_player_b29cf0[index].unknown_20) star=1;
                if(index==0) { unknown_player_b29cf0[index].unknown_20=1;star=2; }
            }
            country=country>0 ? country : 0;
            name.Set(user.name);
            name.To_Lower();
            swprintf(info,L"%hs",user.name);
            for(int j=0;j<(int)wcslen(info);++j) info[j]=(wchar_t)tolower(info[j]);
            SendDlgItemMessageA(window,0x53e,0x4cc,-1,(LPARAM)info);
            cell.Flags=4;
            cell.unknown_0c=player_list_colors_007e6d94[unknown_player_b29cf0[index].unknown_14];
            cell.Secondary.Set(StringTable::Load_String("TXT_UNRANKED",0,"D:\\Ra2\\wonline.cpp",0xce1));
            if(unknown_ladder_cache_b2ac24->Get_Copy(ladder,name)) {
                swprintf(rank,L"%s %d",StringTable::Load_String("TXT_RANK",0,"D:\\Ra2\\wonline.cpp",0xce4),ladder.unknown_1c);
                cell.Secondary.Set(rank);
            }
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b2a81c | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            cell.Flags=1;
            if(strlen(user.unknown_57)) {
                Unknown_006FA0C0(info,user.unknown_2e,-1);
                cell.Secondary.Set(info);
                Unknown_006FA0C0(info,user.unknown_57,-1);
            } else {
                if(unknown_ladder_cache_b2ac24->Get_Copy(ladder,name)) {
                    swprintf(info,L"(%s %d)",StringTable::Load_String("TXT_RANK",0,"D:\\Ra2\\wonline.cpp",0xcf7),ladder.unknown_1c);
                    cell.Secondary.Set(player_list_w_00839d4c);
                } else {
                    swprintf(info,player_list_w_00839d4c);
                    cell.Secondary.Set(player_list_w_00839d4c);
                }
            }
            cell.Text.Set(info);
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b2ab80 | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            cell.Flags=2;
            switch(country) {
            case 0:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("usai.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\wonline.cpp",0xd1b));
                break;
            case 1:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("japi.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\wonline.cpp",0xd1f));
                break;
            case 2:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("frai.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\wonline.cpp",0xd23));
                break;
            case 3:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("geri.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\wonline.cpp",0xd27));
                break;
            case 4:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("gbri.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_GDI",0,"D:\\Ra2\\wonline.cpp",0xd2b));
                break;
            case 5:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("djbi.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\wonline.cpp",0xd2f));
                break;
            case 6:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("arbi.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\wonline.cpp",0xd33));
                break;
            case 7:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("lati.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\wonline.cpp",0xd37));
                break;
            case 8:
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("rusi.pcx",0);
                swprintf(info,L"%s",StringTable::Load_String("TXT_NOD",0,"D:\\Ra2\\wonline.cpp",0xd3b));
                break;
            }
            cell.Secondary.Set(info);
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b292e0 | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            cell.Flags=2;
            if(star) {
                if(star==2) cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolhost.pcx",0);
                else cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolacpt.pcx",0);
                cell.Secondary.Set(StringTable::Load_String("TXT_ACCEPTED",0,"D:\\Ra2\\wonline.cpp",0xd49));
            } else {
                cell.Flags=0;
                cell.Secondary.Set(player_list_w_00839d4c);
            }
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b297b8 | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
            int ping=0;
            unknown_ladder_client_a72d00->Get_Average_Ping(user.unknown_18,&ping);
            if(ping<0) ping=0;
            cell.Flags=3;
            cell.unknown_14=ping;
            wchar_t ping_text[200];
            swprintf(ping_text,StringTable::Load_String("MSG:PingInfo",0,"D:\\Ra2\\wonline.cpp",0xd59),ping);
            if(ping==0) swprintf(ping_text,StringTable::Load_String("TXT_UNKNOWN_PING",0,"D:\\Ra2\\wonline.cpp",0xd5b));
            cell.Secondary.Set(ping_text);
            Wstring ping_name(user.name);
            if(local_name==ping_name.As_Lower()) cell.Flags=0;
            SendDlgItemMessageA(window,0x53e,0x4a8,((unsigned short)player_list_column_00b26958 | ((unsigned int)(unsigned short)i << 16)),(LPARAM)&cell);
        }
    }
    if(!keep_selection) Restore_List_Selection_005c6310(list,&selections);
    int selected=SendDlgItemMessageA(window,0x53e,0x190,0,0);
    int total=unknown_users_b2a728.Count;
    if(selected>0) sprintf(count_text,"%d  (%d)",total,selected);
    else sprintf(count_text,"%d",total);
    SendDlgItemMessageA(window,0x60b,0x4b4,0,(LPARAM)count_text);
    SendDlgItemMessageA(window,0x53e,0x197,top,0);
    SendDlgItemMessageA(window,0x53e,0x49d,0,0);
    InvalidateRect(GetDlgItem(window,0x53e),0,0);
}

// @ref ?Insert@WideString@@QAE_NPBGI@Z=007704c0

// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_07KDFL@TXT_GDI?$AA@=007e69c0
// @ref ??_C@_07LLCA@TXT_NOD?$AA@=007e69b8
// @ref ??_C@_08BLKF@usai?4pcx?$AA@=007eb520
// @ref ??_C@_08CJID@arbi?4pcx?$AA@=007eb4d8
// @ref ??_C@_08CKDM@gbri?4pcx?$AA@=007eb4f0
// @ref ??_C@_08EBLL@?$CFd?5?5?$CI?$CFd?$CJ?$AA@=007fd8cc
// @ref ??_C@_08FLCC@japi?4pcx?$AA@=007eb514
// @ref ??_C@_08GD@TXT_OPER?$AA@=007fd8f4
// @ref ??_C@_08GFEA@TXT_RANK?$AA@=007fd814
// @ref ??_C@_08GPKK@frai?4pcx?$AA@=007eb508
// @ref ??_C@_08HFFD@rusi?4pcx?$AA@=007eb4c0
// @ref ??_C@_08LNEF@lati?4pcx?$AA@=007eb4cc
// @ref ??_C@_08NMOA@djbi?4pcx?$AA@=007eb4e4
// @ref ??_C@_08ODNE@geri?4pcx?$AA@=007eb4fc
// @ref ??_C@_09MKLC@TXT_VOICE?$AA@=007fd8e8
// @ref ??_C@_0BB@ECNN@TXT_UNKNOWN_PING?$AA@=007fd840
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_0M@BDDC@wolhost?4pcx?$AA@=007e69ac
// @ref ??_C@_0M@FIPJ@woloper?4pcx?$AA@=007eb278
// @ref ??_C@_0M@GKHD@wolacpt?4pcx?$AA@=007e69a0
// @ref ??_C@_0N@DCKM@wolvoice?4pcx?$AA@=007eb240
// @ref ??_C@_0N@FIOC@TXT_UNRANKED?$AA@=007fd828
// @ref ??_C@_0N@IEEP@MSG?3PingInfo?$AA@=007fd854
// @ref ??_C@_0N@PKAL@TXT_ACCEPTED?$AA@=007fd8d8
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref ??_C@_17FKIN@?$AA?$CF?$AAh?$AAs?$AA?$AA@=007eadcc
// @ref ??_C@_1BA@BPGE@?$AA?$CI?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAd?$AA?$CJ?$AA?$AA@=007fd900
// @ref ??_C@_1M@CAAD@?$AA?$FL?$AA?$CF?$AAh?$AAs?$AA?$FN?$AA?$AA@=007fd910
// @ref ??_C@_1M@NBJH@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007fd91c
// @ref ??_C@_1M@OLCI@?$AA?$CI?$AA?$CF?$AAh?$AAs?$AA?$CJ?$AA?$AA@=007fd928
