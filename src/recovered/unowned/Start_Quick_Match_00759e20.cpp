// Start_Quick_Match 0x00759E20: quick or WDT match. Leaves any channel, finds the matching lobby, joins it and waits in
// the waiting dialog for the match server. Returns 1 when the game is starting. Original 2,202 B + 6 NOP.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_time.hpp"
#include "shared/debug_printf.hpp"
#include "shared/dialog_create.hpp"
#include "shared/win_util.hpp"
#include "shared/map_preview.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE *,BOOL,DWORD);
extern HANDLE wol_wait_events_b264f8[18];
extern int unknown_b2ac2c,unknown_b2ab88;
extern long unknown_b2a8a4;
extern Wstring unknown_b2997c;
extern HWND game_window_00b263d8;
extern void *ProgramInstance;
extern char wol_source_file_007fd62c[],wol_leave_debug_7fe6f8[],wol_leaving_label_7fe6e4[],wol_joining_label_7fe688[];
extern char wol_wdt_resolution_7ffe14[],wol_quick_resolution_7ffdf4[],wol_no_agent_7ffdd8[],wol_no_server_7ffdb8[];
extern char wol_join_failure_7ffda0[],wol_match_timeout_7fd768[],wol_match_fail_7ffd8c[],wol_match_starting_7ffd74[];
extern char wol_lobby_prefix_35_7fd368[],wol_lobby_prefix_38_7fd360[],wol_lobby_password_7fe738[];
extern "C" int __cdecl _strnicmp(char const *,char const *,unsigned int);
bool __fastcall Test_Display_Mode(int width,int height);
bool __fastcall Get_Channel_List_0073d8f0();
bool __fastcall Request_Channel_List_0073d760(int,unsigned char);
bool __fastcall Unknown_00514EE0();
void __fastcall Collect_Remote_Player_Names_0075a6c0();
void __fastcall Service_Pending_Player_Pings_0075b2d0();
bool __fastcall Start_Match_0075be10();
int __stdcall Wonline_Waiting_Dialog_0075c350(HWND,UINT,WPARAM,LPARAM);
int __stdcall Wonline_Map_Download_Dialog_0075c830(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_show_dialog_5ff7e0(void *,int);
bool __fastcall Queue_Channel_List_Request_0073db20(int channel_type,unsigned char autoping,bool wait);
void __fastcall Reset_Buddy_State_00757720();
// @ref ?Reset_Wait_Events@@YAXXZ=00752930
// @ref ?Start_Match_0075be10@@YI_NXZ=0075be10
// @ref ?wol_wdt_resolution_7ffe14@@3PADA=007ffe14
// @ref ?wol_quick_resolution_7ffdf4@@3PADA=007ffdf4
// @ref ?wol_no_agent_7ffdd8@@3PADA=007ffdd8
// @ref ?wol_no_server_7ffdb8@@3PADA=007ffdb8
// @ref ?wol_join_failure_7ffda0@@3PADA=007ffda0
// @ref ?wol_match_timeout_7fd768@@3PADA=007fd768
// @ref ?wol_match_fail_7ffd8c@@3PADA=007ffd8c
// @ref ?wol_match_starting_7ffd74@@3PADA=007ffd74
// @ref ?wol_lobby_prefix_35_7fd368@@3PADA=007fd368
// @ref ?wol_lobby_prefix_38_7fd360@@3PADA=007fd360
// @ref ?wol_lobby_password_7fe738@@3PADA=007fe738
// @ref __strnicmp=007858d0
inline void __fastcall Set_Matchmaking_State(int state,int timeout,int result)
{
    unknown_b2ac2c=result;
    unknown_b26898=state;
    unknown_b2ab88=timeout;
    unknown_b2a8a4=time(0);
}
inline void Match_Message(char const *label,int line)
{
    Message_Box_005c3230(StringTable::Load_String(label,0,wol_source_file_007fd62c,line),0,Unknown_0073c120,false);
}
int __fastcall Start_Quick_Match_00759e20()
{
    if(unknown_a72c68) {
        unknown_a72c68=0;
        Unknown_005cd540(0);
    }
    unknown_b2abd9=false;
    Set_Matchmaking_State(1,-1,0);
    if(unknown_8523e0>640) {
        WideString query(unknown_session_a3d298.Type==4&&unknown_a3d2a4==2?
            StringTable::Load_String(wol_wdt_resolution_7ffe14,0,wol_source_file_007fd62c,0x64d8):
            StringTable::Load_String(wol_quick_resolution_7ffdf4,0,wol_source_file_007fd62c,0x64d9));
        if(Message_Box_005c3230(query.Get(),4,Unknown_0073c120,true)!=6) return 0;
        if(!Test_Display_Mode(640,480)) return 0;
        Options.ScreenWidth=640;
        Options.ScreenHeight=480;
        Options.Save_Settings();
    }
    unknown_b2ac40=0;
    Unknown_00514EE0();
    Set_Matchmaking_State(2,30,0);
    unknown_lobbies_b26c88.setEmpty();
    unknown_b2997c.Release();
    if(!Request_Chat_Channels()) return 0;
    if(unknown_lobbies_b26c88.Count==0) {
        Match_Message(wol_no_agent_7ffdd8,0x64fb);
        return 0;
    }
    WOL::Channel channel;
    memset(&channel,0,sizeof(channel));
    char const *prefix=unknown_session_a3d298.Type==4&&unknown_a3d2a4==2?wol_lobby_prefix_35_7fd368:wol_lobby_prefix_38_7fd360;
    int i;
    for(i=0;i<unknown_lobbies_b26c88.Count;++i) {
        unknown_lobbies_b26c88.Get(channel,i);
        if(_strnicmp(channel.channel_name,prefix,strlen(prefix))==0) break;
    }
    if(i>=unknown_lobbies_b26c88.Count) {
        Match_Message(wol_no_server_7ffdb8,0x650e);
        return 0;
    }
    HWND dialog=(HWND)unknown_create_dialog_735700(ProgramInstance,0x117,game_window_00b263d8,(UnknownDialogProc)Wonline_Waiting_Dialog_0075c350,0);
    unknown_show_dialog_5ff7e0(dialog,0x117);
    SendMessageA(dialog,0x4a9,0,1);
    ShowWindow(dialog,1);
    Reset_Wait_Events();
    int result=0;
    Reset_Buddy_State_00757720();
    for(;;) {
        if(unknown_b26898==2) {
            int error;
            {
                Wstring password(wol_lobby_password_7fe738);
                error=Request_Channel_Join_00744700(&channel,password,StringTable::Load_String(wol_joining_label_7fe688,0,wol_source_file_007fd62c,0x6526));
            }
            if(error) {
                Set_Matchmaking_State(0,-1,1);
                Match_Message(wol_join_failure_7ffda0,0x6529);
                break;
            }
            Set_Matchmaking_State(3,20,0);
        }
        if(unknown_b26898==3&&unknown_users_b2a728.Count>1&&strcmp(channel.channel_name,unknown_game_channel_b299c0.channel_name)==0) Unknown_0075a920();
        DWORD event;
        while((event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,20))==0x102) Unknown_0073e100();
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==0||event==6) break;
        if(event==0x11) {
            Collect_Remote_Player_Names_0075a6c0();
            Service_Pending_Player_Pings_0075b2d0();
        }
        else if(event==5) {
            if(unknown_b26898==0) {
                Leave_Game_Channel(0x40,false);
                switch(unknown_b2ac2c) {
                case 1:
                    Match_Message(wol_no_agent_7ffdd8,0x656c);
                    break;
                case 2:
                    Match_Message(wol_match_timeout_7fd768,0x6570);
                    break;
                default:
                    Match_Message(wol_match_fail_7ffd8c,0x6574);
                    break;
                }
                break;
            }
        }
        else if(event==0x10) {
            if(Start_Match_0075be10()&&unknown_a3d2a4==2) {
                HWND download=unknown_create_dialog_5ff610(0x11f,(DialogProc)Wonline_Map_Download_Dialog_0075c830,0);
                Set_Matchmaking_State(10,180,0);
                SendMessageA(download,0x4a9,0,1);
                ShowWindow(download,1);
            }
        }
        else if(event==7) {
            Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(wol_match_starting_7ffd74,0,wol_source_file_007fd62c,0x658d));
            unknown_b2ac04=false;
            result=1;
            break;
        }
    }
    End_Dialog_007357e0(dialog,0);
    HWND download=(HWND)Unknown_00735940(0x11f);
    if(download) End_Dialog_007357e0(download,0);
    if(unknown_b26898!=11) Set_Matchmaking_State(1,-1,0);
    Leave_Game_Channel(0x40,true);
    if(unknown_dialog_preview_a72ce8) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8=0;
    }
    return result;
}
