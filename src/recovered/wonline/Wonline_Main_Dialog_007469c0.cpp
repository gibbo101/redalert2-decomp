#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_settings.hpp"
#include "shared/theme.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/crt_string.hpp"
#include "shared/string_table.hpp"
extern HANDLE wol_wait_events_b264f8[18];
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __stdcall unknown_dialog_5ecf40(HWND,int);
namespace OwnerDraw {
void __fastcall unknown_5e6390(HWND);
void __fastcall unknown_5e5150(HWND,bool);
void __fastcall unknown_draw_dialog_back_5fee70(HWND);
}
void __fastcall unknown_5159b0(int,bool);
void __fastcall Unknown_005CD3A0();
void __fastcall Unknown_005FE380(long);
WideString __fastcall Limit_Name_Text_005ccf50(HWND);
LRESULT __fastcall unknown_get_window_wide_text(HWND,WideString &);
int __fastcall Unknown_0073cb80(WideString const &);
int __fastcall Unknown_0073ca50(WideString const &);
int __fastcall Parse_Page_Command_00746480(wchar_t const *);
int __fastcall Reply_To_Last_Pager_007466c0(wchar_t const *);
int __fastcall Parse_Online_Command_00746240(wchar_t const *);
void __fastcall Refresh_Lobby_List_0073ee80();
void __fastcall Refresh_Game_List_0073f8f0();
void __fastcall Refresh_Wonline_Players_0073fee0(int,bool);
WideString __fastcall Game_List_Row_Text_0073f5f0(HWND,int);
WideString __fastcall User_List_Row_Text_0073f850(HWND,int);
bool __fastcall Request_Chat_Channel_List_0073dd20(bool wait);
bool __fastcall Request_Game_Channel_List_0073df10(unsigned char autoping,bool wait);
bool __fastcall Can_Join_Channel_00755cd0(WOL::Channel const *,bool,bool);
bool __fastcall Join_Game_Channel_00745780(WOL::Channel const *,bool);
bool __fastcall Host_Game_007459a0();
void __fastcall View_HTML_0073c580(char const *,int);
HWND __fastcall unknown_create_dialog_5ff610(int,int (__stdcall *)(HWND,UINT,WPARAM,LPARAM),int);
int __fastcall Dialog_Loop_007359e0(HWND,bool (*)(),int,bool,bool);
bool connection_wait_callback_0073c120();
int __stdcall Wonline_Options_Dialog_00749b50(HWND,UINT,WPARAM,LPARAM);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *,wchar_t const *,unsigned);
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned);
extern "C" long __cdecl atol(char const *);
extern wchar_t wol_empty_text_839d4c[];
extern int unknown_color_7a7368,unknown_color_7a736c,unknown_color_7a7370,unknown_color_7a737c;
extern int wol_lan_leave_b2abf0;
extern int unknown_b2abec;
extern int unknown_a3d2a4,unknown_online_option_a3d2a8;
extern unsigned int game_type_column_b2a6f8,game_private_column_b2a6f4,game_observer_column_b299a0,game_name_column_b2a8a8,game_ping_column_b292a8,lobby_title_column_b29acc;
extern int player_list_column_00b2657c,player_list_column_00b2a81c,player_list_column_00b292a4;
extern int wol_pending_allow_page_b292e4,wol_pending_allow_find_b294f0,wol_pending_lang_filter_b29810,wol_pending_lob_music_b297cc;
extern int wol_pending_show_all_b2a644,wol_pending_display_asian_b29730,wol_pending_display_latin_b29978;
extern int last_game_data_7fd378,last_game_data_7fd37c;
extern char last_game_name_b2ac84[];
extern bool game_list_refreshing_b2ac80;
extern char wol_source_file_007fd62c[];
extern char wol_label_7fe9fc[],wol_label_7fe9e8[],wol_label_7dfc7c[],wol_label_7fe9d4[],wol_label_7dfc64[],wol_label_7dfc48[];
extern char wol_label_7dfc14[],wol_label_7dfbfc[],wol_label_7fe998[],wol_label_7fd358[],wol_label_7e1a60[];
extern wchar_t wol_label_7fe2c4[],wol_label_7fe9b8[],wol_label_7fe9a4[],wol_label_7d64f4[];
extern char wol_label_7eb2e4[],wol_label_7eb2d8[],wol_label_7eb2cc[],wol_label_7eb2c0[],wol_label_7fd564[];
void __fastcall Apply_WOL_Settings_0073c990();
inline void Refresh_Game_Channels()
{
    if(!Request_Game_Channel_List_0073df10(1,false)) SetEvent(wol_wait_events_b264f8[5]);
}
inline void Refresh_Chat_Channels()
{
    if(!Request_Chat_Channel_List_0073dd20(false)) SetEvent(wol_wait_events_b264f8[5]);
}
inline void Update_Game_Channels(HWND window)
{
    if(Unknown_00735B10()==window) Refresh_Game_Channels();
}
inline void Update_Chat_Channels(HWND window)
{
    if(Unknown_00735B10()==window) Refresh_Chat_Channels();
}
inline bool Request_Channel_Lists()
{
    return Request_Chat_Channel_List_0073dd20(true) && Request_Game_Channel_List_0073df10(1,false);
}
inline void Refresh_Channel_Lists()
{
    if(!Request_Channel_Lists()) SetEvent(wol_wait_events_b264f8[5]);
}
inline void On_Lobby_Timer(HWND window,WPARAM timer)
{
    switch(timer) {
    case 0x55d:
        KillTimer(window,0x55d);
        EnableWindow(GetDlgItem(window,0x55d),1);
        break;
    case 1:
        Update_Chat_Channels(window);
        break;
    case 0:
        Update_Game_Channels(window);
        break;
    }
}
inline void On_Refresh_Lists(HWND window)
{
    EnableWindow(GetDlgItem(window,0x53d),0);
    Refresh_Channel_Lists();
    EnableWindow(GetDlgItem(window,0x53d),1);
}
// @ref ?Grow@WolIntArray@@QAE_NXZ=00768290
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_5e5150@OwnerDraw@@YIXPAUHWND__@@_N@Z=005e5150
// @ref ?Refresh_Lobby_List_0073ee80@@YIXXZ=0073ee80
// @ref ?Refresh_Game_List_0073f8f0@@YIXXZ=0073f8f0
// @ref ?Refresh_Wonline_Players_0073fee0@@YIXH_N@Z=0073fee0
// @ref ?Host_Game_007459a0@@YI_NXZ=007459a0
// @ref ?Wonline_Options_Dialog_00749b50@@YGHPAUHWND__@@IIJ@Z=00749b50
// @ref _wcsncpy=00783622
// @ref _wcsncmp=007846cc
// @ref _atol=00782d72
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_empty_text_839d4c@@3PAGA=00839d4c
// @ref ?unknown_color_7a7368@@3HA=007a7368
// @ref ?unknown_color_7a736c@@3HA=007a736c
// @ref ?unknown_color_7a7370@@3HA=007a7370
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?wol_lan_leave_b2abf0@@3HA=00b2abf0
// @ref ?unknown_b2abec@@3HA=00b2abec
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?unknown_online_option_a3d2a8@@3HA=00a3d2a8
// @ref ?game_type_column_b2a6f8@@3IA=00b2a6f8
// @ref ?game_private_column_b2a6f4@@3IA=00b2a6f4
// @ref ?game_observer_column_b299a0@@3IA=00b299a0
// @ref ?game_name_column_b2a8a8@@3IA=00b2a8a8
// @ref ?game_ping_column_b292a8@@3IA=00b292a8
// @ref ?lobby_title_column_b29acc@@3IA=00b29acc
// @ref ?player_list_column_00b2657c@@3HA=00b2657c
// @ref ?player_list_column_00b2a81c@@3HA=00b2a81c
// @ref ?player_list_column_00b292a4@@3HA=00b292a4
// @ref ?wol_pending_allow_page_b292e4@@3HA=00b292e4
// @ref ?wol_pending_allow_find_b294f0@@3HA=00b294f0
// @ref ?wol_pending_lang_filter_b29810@@3HA=00b29810
// @ref ?wol_pending_lob_music_b297cc@@3HA=00b297cc
// @ref ?wol_pending_show_all_b2a644@@3HA=00b2a644
// @ref ?wol_pending_display_asian_b29730@@3HA=00b29730
// @ref ?wol_pending_display_latin_b29978@@3HA=00b29978
// @ref ?last_game_data_7fd378@@3HA=007fd378
// @ref ?last_game_data_7fd37c@@3HA=007fd37c
// @ref ?last_game_name_b2ac84@@3PADA=00b2ac84
// @ref ?game_list_refreshing_b2ac80@@3_NA=00b2ac80
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_label_7fe9fc@@3PADA=007fe9fc
// @ref ?wol_label_7fe9e8@@3PADA=007fe9e8
// @ref ?wol_label_7dfc7c@@3PADA=007dfc7c
// @ref ?wol_label_7fe9d4@@3PADA=007fe9d4
// @ref ?wol_label_7dfc64@@3PADA=007dfc64
// @ref ?wol_label_7dfc48@@3PADA=007dfc48
// @ref ?wol_label_7dfc14@@3PADA=007dfc14
// @ref ?wol_label_7dfbfc@@3PADA=007dfbfc
// @ref ?wol_label_7fe998@@3PADA=007fe998
// @ref ?wol_label_7fd358@@3PADA=007fd358
// @ref ?wol_label_7e1a60@@3PADA=007e1a60
// @ref ?wol_label_7fe2c4@@3PAGA=007fe2c4
// @ref ?wol_label_7fe9b8@@3PAGA=007fe9b8
// @ref ?wol_label_7fe9a4@@3PAGA=007fe9a4
// @ref ?wol_label_7d64f4@@3PAGA=007d64f4
// @ref ?wol_label_7eb2e4@@3PADA=007eb2e4
// @ref ?wol_label_7eb2d8@@3PADA=007eb2d8
// @ref ?wol_label_7eb2cc@@3PADA=007eb2cc
// @ref ?wol_label_7eb2c0@@3PADA=007eb2c0
// @ref ?wol_label_7fd564@@3PADA=007fd564
int __stdcall Wonline_Main_Dialog_007469c0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    switch(message) {
    case 2:
        KillTimer(window,0);
        KillTimer(window,0x55d);
        Unknown_005CD3A0();
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0xf:
        OwnerDraw::unknown_draw_dialog_back_5fee70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 7:
        SetFocus(GetDlgItem(window,0x540));
        break;
    case 0x14:
        return 1;
    case 0x18:
        return 0;
    case 0x111:
        switch((int)(wparam&0xffff)) {
        case 0x53d: {
            int selection=SendMessageA((HWND)lparam,0x188,0,0);
            if(selection==-1) return 0;
            int data=SendMessageA((HWND)lparam,0x199,selection,0);
            if((unsigned short)(wparam>>16)==1 && data!=-1) {
                WOL::Channel lobby;
                if(unknown_lobbies_b26c88.Get(lobby,data) && strcmp(lobby.name,unknown_channel_b299c0.name) && strcmp(lobby.name,unknown_pending_channel_b26a60.name)) {
                    wol_lan_leave_b2abf0=1;
                    unknown_b2abec=atol(lobby.name+strlen(wol_label_7fd358));
                    SetEvent(wol_wait_events_b264f8[9]);
                }
            }
            return 0;
        }
        case 0x53e:
            return 0;
        case 0x3ed: {
            HWND input=GetDlgItem(window,0x540);
            WideString text=Limit_Name_Text_005ccf50(input);
            SendMessageA(input,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
            SetFocus(input);
            InvalidateRect(input,0,0);
            int color=unknown_color_7a7370;
            if(strlen(unknown_channel_b299c0.name)==0)
                Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7fe9fc,0,wol_source_file_007fd62c,0x2c52));
            else if(text.Length()>0) {
                if(Unknown_0073cb80(text)) color=unknown_color_7a736c;
                Unknown_005C2C80(color,wol_label_7fe2c4,unknown_wstring_b26cb8.Buffer,text.Get());
            } else Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7fe9e8,0,wol_source_file_007fd62c,0x2c5a));
            return 0;
        }
        case 0x540: {
            wchar_t nickname[16],primary_command[64],alternate_command[64];
            HWND input=GetDlgItem(window,0x540);
            WideString text=Limit_Name_Text_005ccf50(input);
            if((unsigned short)(wparam>>16)==0x501) {
                SendMessageA(input,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
                if(text.Length()>0) {
                    int parsed=Parse_Page_Command_00746480(text.Get());
                    if(parsed!=0) {
                        if(parsed==1) {
                            int count=0;
                            unsigned length=text.Length()+1;
                            wchar_t *copy=(wchar_t *)operator new(length*2);
                            wcscpy(primary_command,StringTable::Load_String(wol_label_7dfc7c,0,wol_source_file_007fd62c,0x2bd9));
                            if(!copy) return 0;
                            copy=wcsncpy(copy,text.Get(),length);
                            if(!copy) return 0;
                            wchar_t *body=copy+wcslen(primary_command);
                            while(*body && wcsncmp(body,wol_label_7d64f4,1)==0) ++body;
                            while(*body) {
                                if(wcsncmp(body,wol_label_7d64f4,1)==0 || count>10) break;
                                nickname[count++]=*body++;
                            }
                            nickname[count]=0;
                            while(*body && wcsncmp(body,wol_label_7d64f4,1)==0) ++body;
                            if(count>10) Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7fe9d4,0,wol_source_file_007fd62c,0x2bf7));
                            else if(count==0) Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7dfc64,0,wol_source_file_007fd62c,0x2bf9));
                            else if(wcslen(body)>0) Unknown_005C2C80(unknown_color_7a7368,wol_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                            else Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7dfc48,0,wol_source_file_007fd62c,0x2bff));
                            operator delete(copy);
                        }
                    } else if(Reply_To_Last_Pager_007466c0(text.Get())) {
                        unsigned length=text.Length()+1;
                        wchar_t *copy=(wchar_t *)operator new(length*2);
                        wcscpy(primary_command,StringTable::Load_String(wol_label_7dfc14,0,wol_source_file_007fd62c,0x2c11));
                        wcscpy(alternate_command,StringTable::Load_String(wol_label_7dfbfc,0,wol_source_file_007fd62c,0x2c12));
                        if(!copy) return 0;
                        copy=wcsncpy(copy,text.Get(),length);
                        if(!copy) return 0;
                        wchar_t *body=copy+(wcsncmp(copy,primary_command,wcslen(primary_command))==0 ? wcslen(primary_command):wcslen(alternate_command));
                        while(*body && wcsncmp(body,wol_label_7d64f4,1)==0) ++body;
                        wcscpy(nickname,Unknown_006FA180(unknown_last_pager_b2ac48));
                        if(wcslen(nickname)>0 && wcslen(body)>0)
                            Unknown_005C2C80(unknown_color_7a7368,wol_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                        else if(wcslen(nickname)>0)
                            Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7dfc48,0,wol_source_file_007fd62c,0x2c2f));
                        operator delete(copy);
                    } else if(!Parse_Online_Command_00746240(text.Get())) {
                        if(strlen(unknown_channel_b299c0.name)==0) {
                            Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7fe9fc,0,wol_source_file_007fd62c,0x2c38));
                            return 0;
                        }
                        int color=unknown_color_7a737c;
                        if(Unknown_0073ca50(text)==1) color=unknown_color_7a7368;
                        Unknown_005C2C80(color,wol_label_7fe9a4,unknown_wstring_b26cb8.Buffer,text.Get());
                    }
                }
            }
            return 0;
        }
        case 0x55d:
            EnableWindow((HWND)lparam,0);
            SetTimer(window,0x55d,3000,0);
            Refresh_Game_Channels();
            break;
        case 0x558:
            View_HTML_0073c580(wol_label_7fd564,0);
            SetFocus(GetDlgItem(window,0x540));
            break;
        case 0x608: {
            WideString text;
            HWND input=GetDlgItem(window,0x540);
            unknown_get_window_wide_text(input,text);
            SendMessageA(input,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
            SetFocus(input);
            if(unknown_squad_id_b2abfc) {
                WOL::User user;
                memset(&user,0,sizeof(user));
                strcpy(user.name,wol_label_7e1a60);
                unknown_chat_a72cfc->unknown_slot59(&user,text.Get());
            } else Unknown_005C2C80(-1,StringTable::Load_String(wol_label_7fe998,0,wol_source_file_007fd62c,0x2c74));
            return 0;
        }
        case 0x62d: {
            HWND list=GetDlgItem(window,0x6ee);
            int selection=SendMessageA(list,0x188,0,0);
            bool enable=false;
            int data=-1;
            if(selection!=-1) {
                data=SendMessageA(list,0x199,selection,0);
                if(data>=0 && data<unknown_games_b29990.Count) {
                    WOL::Channel game;
                    memset(&game,0,sizeof(game));
                    game=unknown_games_b29990.Items[data];
                    enable=Can_Join_Channel_00755cd0(&game,data!=last_game_data_7fd378,unknown_a72c68!=0);
                    if(enable) {
                        EnableWindow(GetDlgItem(window,0x62b),0);
                        EnableWindow(GetDlgItem(window,0x62d),0);
                        SendMessageA(GetDlgItem(window,0x6ee),0x186,-1,0);
                        EnableWindow(GetDlgItem(window,0x689),0);
                        EnableWindow(GetDlgItem(window,0x558),0);
                        EnableWindow(GetDlgItem(window,0x61f),0);
                        EnableWindow(GetDlgItem(window,0x686),0);
                        bool joined=Join_Game_Channel_00745780(&game,unknown_a72c68==1);
                        EnableWindow(GetDlgItem(window,0x62b),1);
                        EnableWindow(GetDlgItem(window,0x689),1);
                        EnableWindow(GetDlgItem(window,0x558),1);
                        EnableWindow(GetDlgItem(window,0x61f),1);
                        EnableWindow(GetDlgItem(window,0x686),1);
                        if(joined) {
                            OwnerDraw::unknown_5e5150(window,false);
                            unknown_5159b0(0,true);
                            ShowWindow(window,0);
                            unknown_dialog_5ecf40(window,1);
                        }
                    }
                }
            }
            last_game_data_7fd378=data;
            EnableWindow((HWND)lparam,enable);
            SetFocus(GetDlgItem(window,0x540));
            break;
        }
        case 0x62b: {
            EnableWindow((HWND)lparam,0);
            EnableWindow(GetDlgItem(window,0x62d),0);
            SendMessageA(GetDlgItem(window,0x6ee),0x186,-1,0);
            EnableWindow(GetDlgItem(window,0x689),0);
            EnableWindow(GetDlgItem(window,0x558),0);
            EnableWindow(GetDlgItem(window,0x61f),0);
            EnableWindow(GetDlgItem(window,0x686),0);
            bool hosted=Host_Game_007459a0();
            EnableWindow((HWND)lparam,1);
            EnableWindow(GetDlgItem(window,0x689),1);
            EnableWindow(GetDlgItem(window,0x558),1);
            EnableWindow(GetDlgItem(window,0x61f),1);
            EnableWindow(GetDlgItem(window,0x686),1);
            if(!hosted) SetFocus(GetDlgItem(window,0x540));
            break;
        }
        case 0x61f: {
            OwnerDraw::unknown_5e5150(window,false);
            unknown_5159b0(0,true);
            HWND dialog=unknown_create_dialog_5ff610(700,Wonline_Options_Dialog_00749b50,0);
            ShowWindow(dialog,1);
            int result=Dialog_Loop_007359e0(dialog,connection_wait_callback_0073c120,0,true,true);
            InvalidateRect(window,0,0);
            ShowWindow(window,5);
            unknown_dialog_5ecf40(window,0);
            if(result==2) Apply_WOL_Settings_0073c990();
            else {
                unknown_wol_allow_page_b290a0=wol_pending_allow_page_b292e4;
                unknown_wol_allow_find_b2a818=wol_pending_allow_find_b294f0;
                unknown_wol_lang_filter_b2a7e4=wol_pending_lang_filter_b29810;
                unknown_wol_lob_music_b297c8=wol_pending_lob_music_b297cc;
                unknown_wol_show_all_b2a634=wol_pending_show_all_b2a644;
                unknown_wol_display_asian_b2a804=wol_pending_display_asian_b29730;
                unknown_wol_display_latin_b2a7e8=wol_pending_display_latin_b29978;
                Unknown_WOL_Save_Settings_0073C890();
                Apply_WOL_Settings_0073c990();
            }
            SetFocus(GetDlgItem(window,0x540));
            return 0;
        }
        case 0x547: case 0x5c0: case 0x686:
            OwnerDraw::unknown_5e6390(window);
            SetEvent(wol_wait_events_b264f8[6]);
            return 0;
        case 0x689:
            unknown_a3d2a4=4;
            unknown_online_option_a3d2a8=3;
            OwnerDraw::unknown_5e6390(window);
            SetEvent(wol_wait_events_b264f8[6]);
            return 0;
        case 0x6ee: {
            bool activate=false;
            switch(wparam>>16) {
            case 1: break;
            case 2: activate=true; break;
            default: return 0;
            }
            int selection=SendMessageA((HWND)lparam,0x188,0,0);
            int data=-1;
            bool enable=false;
            if(selection!=-1) {
                data=SendMessageA((HWND)lparam,0x199,selection,0);
                if(data>=0 && data<unknown_games_b29990.Count) {
                    WOL::Channel game;
                    memset(&game,0,sizeof(game));
                    game=unknown_games_b29990.Items[data];
                    if(last_game_data_7fd37c==-1) last_game_name_b2ac84[0]=0;
                    int changed=strcmp(last_game_name_b2ac84,game.name);
                    enable=Can_Join_Channel_00755cd0(&game,activate || changed,unknown_a72c68!=0);
                    strcpy(last_game_name_b2ac84,game.name);
                    if(enable && activate) {
                        EnableWindow(GetDlgItem(window,0x62b),0);
                        EnableWindow(GetDlgItem(window,0x62d),0);
                        SendMessageA(GetDlgItem(window,0x6ee),0x186,-1,0);
                        EnableWindow(GetDlgItem(window,0x689),0);
                        EnableWindow(GetDlgItem(window,0x558),0);
                        EnableWindow(GetDlgItem(window,0x61f),0);
                        EnableWindow(GetDlgItem(window,0x686),0);
                        if(Join_Game_Channel_00745780(&game,unknown_a72c68==1)) {
                            OwnerDraw::unknown_5e5150(window,false);
                            unknown_5159b0(0,true);
                            ShowWindow(window,0);
                            unknown_dialog_5ecf40(window,1);
                        }
                        EnableWindow(GetDlgItem(window,0x62b),1);
                        EnableWindow(GetDlgItem(window,0x689),1);
                        EnableWindow(GetDlgItem(window,0x558),1);
                        EnableWindow(GetDlgItem(window,0x61f),1);
                        EnableWindow(GetDlgItem(window,0x686),1);
                    }
                } else last_game_name_b2ac84[0]=0;
            }
            int current=SendMessageA((HWND)lparam,0x188,0,0);
            if(!game_list_refreshing_b2ac80 || current!=-1) last_game_data_7fd37c=data;
            if(game_list_refreshing_b2ac80 && current==-1) game_list_refreshing_b2ac80=false;
            HWND join=GetDlgItem(window,0x62d);
            EnableWindow(join,enable);
            return 0;
        }
        case 0x75f: case 0x760: {
            int checked=0;
            HWND button=GetDlgItem(window,0x760);
            if(button) checked=SendMessageA(button,0xf0,0,0);
            if((unsigned short)wparam==0x75f) checked=!checked;
            unknown_a72c68=checked;
            Unknown_005cd540(0);
            return 0;
        }
        }
        return 0;
    case 0x497: {
        Unknown_005cd540(window);
        SendDlgItemMessageA(window,0x3ed,0x49c,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2e4,0));
        SendDlgItemMessageA(window,0x3ed,0x4aa,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2d8,0));
        SendDlgItemMessageA(window,0x55d,0x49c,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2cc,0));
        SendDlgItemMessageA(window,0x55d,0x4aa,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2c0,0));
        game_type_column_b2a6f8=2;
        game_private_column_b2a6f4=0x13;
        game_observer_column_b299a0=0x24;
        game_name_column_b2a8a8=0x35;
        game_ping_column_b292a8=200;
        SendDlgItemMessageA(window,0x6ee,0x4a6,game_ping_column_b292a8-game_name_column_b2a8a8,game_name_column_b2a8a8);
        SendDlgItemMessageA(window,0x6ee,0x4a6,0,game_type_column_b2a6f8);
        SendDlgItemMessageA(window,0x6ee,0x4a6,0,game_private_column_b2a6f4);
        SendDlgItemMessageA(window,0x6ee,0x4a6,0,game_ping_column_b292a8);
        SendDlgItemMessageA(window,0x6ee,0x4a6,0,game_observer_column_b299a0);
        lobby_title_column_b29acc=2;
        SendDlgItemMessageA(window,0x53d,0x4a6,0,lobby_title_column_b29acc);
        player_list_column_00b2657c=2;
        player_list_column_00b2a81c=0x12;
        player_list_column_00b292a4=0x73;
        SendDlgItemMessageA(window,0x53e,0x4a6,player_list_column_00b292a4-player_list_column_00b2a81c,player_list_column_00b2a81c);
        SendDlgItemMessageA(window,0x53e,0x4a6,0,player_list_column_00b2657c);
        SendDlgItemMessageA(window,0x53e,0x4a6,0,player_list_column_00b292a4);
        Refresh_Lobby_List_0073ee80();
        Refresh_Game_List_0073f8f0();
        Refresh_Wonline_Players_0073fee0(0,false);
        SetFocus(GetDlgItem(window,0x540));
        SetTimer(window,0,30000,0);
        SetTimer(window,1,53000,0);
        return 0;
    }
    case 0x113:
        On_Lobby_Timer(window,wparam);
        break;
    case 0x4e9: {
        OwnerDraw::UnknownTextRequest *request=(OwnerDraw::UnknownTextRequest *)lparam;
        if(request) {
            switch(GetDlgCtrlID((HWND)request->unknown_00)) {
            case 0x6ee:
                request->text=Game_List_Row_Text_0073f5f0((HWND)request->unknown_00,request->unknown_04);
                break;
            case 0x53e:
                request->text=User_List_Row_Text_0073f850((HWND)request->unknown_00,request->unknown_04);
                break;
            }
        }
        return 0;
    }
    case 0x593:
        On_Refresh_Lists(window);
        break;
    case 0x4ed:
        ShowWindow(window,0);
        unknown_dialog_5ecf40(window,1);
        return 0;
    }
    return 0;
}
