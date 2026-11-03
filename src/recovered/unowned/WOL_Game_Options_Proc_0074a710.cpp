#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/options_dialog.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/progress_screen.hpp"
#include "shared/map_preview.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/crt_string.hpp"
namespace OwnerDraw {
WideString __fastcall unknown_5e2160(HWND,int);
WideString __fastcall unknown_5e2260(unsigned int,HWND);
}
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __stdcall unknown_dialog_5ecf40(HWND,int);
void __fastcall Unknown_0073FEE0(int,bool);
wchar_t *__fastcall Player_Info_Tooltip_0074a120(wchar_t const *);
wchar_t *__fastcall Unknown_0074a4e0(wchar_t const *);
int __fastcall Unknown_0073cb80(WideString const &);
int __fastcall Unknown_0073ca50(WideString const &);
int __fastcall Parse_Page_Command_00746480(wchar_t const *);
int __fastcall Reply_To_Last_Pager_007466c0(wchar_t const *);
int __fastcall Parse_Online_Command_00746240(wchar_t const *);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *,wchar_t const *,unsigned);
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned);
extern wchar_t guest_empty_wide_839d4c[];
extern char guest_last_pager_b2ac48[];
extern int guest_action_color_7a7370,guest_private_action_color_7a736c;
extern int guest_chat_color_7a737c,guest_private_color_7a7368;
// @ref ?unknown_5e2160@OwnerDraw@@YI?AVWideString@@PAUHWND__@@H@Z=005e2160
// @ref ?unknown_5e2260@OwnerDraw@@YI?AVWideString@@IPAUHWND__@@@Z=005e2260
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?Unknown_0073FEE0@@YIXH_N@Z=0073fee0
// @ref ?Player_Info_Tooltip_0074a120@@YIPAGPBG@Z=0074a120
// @ref ?Parse_Page_Command_00746480@@YIHPBG@Z=00746480
// @ref ?Reply_To_Last_Pager_007466c0@@YIHPBG@Z=007466c0
// @ref ?guest_empty_wide_839d4c@@3PAGA=00839d4c
// @ref ?guest_last_pager_b2ac48@@3PADA=00b2ac48
// @ref ?guest_action_color_7a7370@@3HA=007a7370
// @ref ?guest_private_action_color_7a736c@@3HA=007a736c
// @ref ?guest_chat_color_7a737c@@3HA=007a737c
// @ref ?guest_private_color_7a7368@@3HA=007a7368
// @ref _wcsncpy=00783622
// @ref _wcsncmp=007846cc
extern char guest_label_7fe9fc[];
// @ref ?guest_label_7fe9fc@@3PADA=007fe9fc
extern char guest_label_7fe9e8[];
// @ref ?guest_label_7fe9e8@@3PADA=007fe9e8
extern wchar_t guest_label_7fe2c4[];
// @ref ?guest_label_7fe2c4@@3PAGA=007fe2c4
extern char guest_label_7dfc7c[];
// @ref ?guest_label_7dfc7c@@3PADA=007dfc7c
extern wchar_t guest_label_7d64f4[];
// @ref ?guest_label_7d64f4@@3PAGA=007d64f4
extern char guest_label_7fe9d4[];
// @ref ?guest_label_7fe9d4@@3PADA=007fe9d4
extern char guest_label_7dfc64[];
// @ref ?guest_label_7dfc64@@3PADA=007dfc64
extern wchar_t guest_label_7fe9b8[];
// @ref ?guest_label_7fe9b8@@3PAGA=007fe9b8
extern char guest_label_7dfc48[];
// @ref ?guest_label_7dfc48@@3PADA=007dfc48
extern char guest_label_7dfc14[];
// @ref ?guest_label_7dfc14@@3PADA=007dfc14
extern char guest_label_7dfbfc[];
// @ref ?guest_label_7dfbfc@@3PADA=007dfbfc
extern wchar_t guest_label_7fe9a4[];
// @ref ?guest_label_7fe9a4@@3PAGA=007fe9a4
extern char guest_label_7e8fe8[];
// @ref ?guest_label_7e8fe8@@3PADA=007e8fe8
extern char guest_label_7e8e28[];
// @ref ?guest_label_7e8e28@@3PADA=007e8e28
extern char guest_label_7eb2e4[];
// @ref ?guest_label_7eb2e4@@3PADA=007eb2e4
extern char guest_label_7eb2d8[];
// @ref ?guest_label_7eb2d8@@3PADA=007eb2d8
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
void __fastcall Save_Lobby_Options_005cc890(HWND,UnknownGameOptions *);
void __fastcall Change_Scenario_Slots_005cb8d0(HWND,int,int);
bool __fastcall Unknown_005c9320(NodeNameType *);
void __fastcall Unknown_0073c480();
void __fastcall Unknown_0075b1b0();
void Request_All_User_Pings_0075af80();
void __fastcall Update_Channel_Player_Limit_00749f20();
void Unknown_Enable_Start_005c9700();
bool __fastcall Unknown_005c93a0(NodeNameType *);
bool __fastcall Unknown_Clear_Closed_Slots_005cacb0(HWND);
void __fastcall Unknown_005cca30(HWND,UnknownGameOptions *);
void __fastcall Unknown_005e5150(HWND,bool);
extern "C" char *__stdcall inet_ntoa(unsigned long);

extern bool host_scenario_enabled_7e6dc0;
extern int host_leave_b2abf0;
extern unsigned long host_version_a3d8d4;
extern char host_scenario_file_a3d8f0[];
extern char host_label_7e6b84[];
extern char host_label_7fec6c[];
extern char host_label_7e6b74[];
extern char host_label_7e6b5c[];
extern char host_label_7fec54[];
extern char host_label_7fec3c[];
extern char host_label_7e24cc[];
extern char host_label_7fec24[];
extern char host_label_7fec10[];
extern char ping_request_debug_007fdde0[];
// @ref ?ping_request_debug_007fdde0@@3PADA=007fdde0
static void Apply_Channel_Restrictions(HWND window)
{
    if(Unknown_0073c370()) {

                EnableWindow(GetDlgItem(window,0x552),0); EnableWindow(GetDlgItem(window,0x553),0); EnableWindow(GetDlgItem(window,0x597),0);
                unknown_session_a3d298.AICount=0; unknown_session_a3d298.unknown_a4=false;
                HWND control=GetDlgItem(window,0x54e); SendMessageA(control,0xf1,1,0); EnableWindow(control,0);
                control=GetDlgItem(window,0x54b); SendMessageA(control,0xf1,1,0); EnableWindow(control,0);
                unknown_session_a3d2c2=1; unknown_flag_a3d2b8=true;
            
    }
}
int __stdcall WOL_Game_Options_Proc_0074a710(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    if(!unknown_b2ac40) {
        switch(message) {
        case 0x497:
            Apply_Channel_Restrictions(window);
            Unknown_Fill_Options_Dialog_005c3550(window,1); break;
        case 0x114:
            if((short)wparam==8) {
                if(GetDlgItem(window,0x54f)) unknown_session_a3d2d0=SendDlgItemMessageA(window,0x54f,0x400,0,0);
                if(GetDlgItem(window,0x402)) unknown_session_a3d2bc=SendDlgItemMessageA(window,0x402,0x400,0,0);
                if(GetDlgItem(window,0x529)) unknown_session_a3d298.GameSpeed_30=6-SendDlgItemMessageA(window,0x529,0x400,0,0);
            for(int accepted=(int)&unknown_player_b29cf0[1].unknown_20;accepted<(int)&unknown_player_b29cf0[8].unknown_20;accepted+=sizeof(WolPlayerData)) *(int *)accepted=0;
            Unknown_Enable_Start_005c9700(); Unknown_0073FEE0(0,false);
            }
            break;
        case 0x111: {
            bool changed=false;
            switch((int)(wparam&0xffff)) {
            case 0x3e8: unknown_session_a3d298.unknown_a8=false; if(SendDlgItemMessageA(window,0x3e8,0xf0,0,0)==1) unknown_session_a3d298.unknown_a8=true; changed=true; break;
            case 0x54d: unknown_flag_a3d2c1=false; if(SendDlgItemMessageA(window,0x54d,0xf0,0,0)==1) unknown_flag_a3d2c1=true; changed=true; break;
            case 0x551: unknown_session_a3d298.unknown_34=false; if(SendDlgItemMessageA(window,0x551,0xf0,0,0)==1) unknown_session_a3d298.unknown_34=true; changed=true; break;
            case 0x596: unknown_session_a3d33d=false; if(SendDlgItemMessageA(window,0x596,0xf0,0,0)==1) unknown_session_a3d33d=true; changed=true; break;
            case 0x597: unknown_session_a3d298.unknown_a4=false; if(SendDlgItemMessageA(window,0x597,0xf0,0,0)==1) unknown_session_a3d298.unknown_a4=true; changed=true; break;
            case 0x599: unknown_session_fog_a3d33f=false; if(SendDlgItemMessageA(window,0x599,0xf0,0,0)==1) unknown_session_fog_a3d33f=true; changed=true; break;
            case 0x624: unknown_session_a3d2c0=false; if(SendDlgItemMessageA(window,0x624,0xf0,0,0)==1) unknown_session_a3d2c0=true; changed=true; break;
            case 0x69a: unknown_session_a3d2c3=false; if(SendDlgItemMessageA(window,0x69a,0xf0,0,0)==1) unknown_session_a3d2c3=true;  break;
            case 0x54b:
                unknown_flag_a3d2b8=false;
                if(SendDlgItemMessageA(window,0x54b,0xf0,0,0)==1) unknown_flag_a3d2b8=true;
                else if(!unknown_flag_a3d2b8) { unknown_session_a3d2c2=0; SendDlgItemMessageA(window,0x54e,0xf1,0,0); }
                changed=true; break;
            case 0x54e:
                unknown_session_a3d2c2=0;
                if(SendDlgItemMessageA(window,0x54e,0xf0,0,0)==1) { unknown_session_a3d2c2=1; if(!unknown_flag_a3d2b8) { unknown_flag_a3d2b8=true; SendDlgItemMessageA(window,0x54b,0xf1,1,0); } }
                changed=true; break;
            case 0x69d:
                unknown_session_a3d298.unknown_2c=false;
                if(SendDlgItemMessageA(window,0x69d,0xf0,0,0)==1) unknown_session_a3d298.unknown_2c=true;
                break;
            }
            if(changed) {
            for(int accepted=(int)&unknown_player_b29cf0[1].unknown_20;accepted<(int)&unknown_player_b29cf0[8].unknown_20;accepted+=sizeof(WolPlayerData)) *(int *)accepted=0;
            Unknown_Enable_Start_005c9700(); Unknown_0073FEE0(0,false);
            }
            break;
        }
        }
    }
    switch(message) {
    case 0x84: {
        HWND tooltip=GetDlgItem(window,0x695);
        if(!tooltip) goto host_unhandled;
        POINT point;
        point.x=lparam&0xffff;
        point.y=(unsigned)lparam>>16;
        RECT bounds;
        GetWindowRect(window,&bounds);
        point.x-=bounds.left;
        point.y-=bounds.top;
        WideString text;
        HWND child=ChildWindowFromPointEx(window,point,1);
        if(child) {
            text=OwnerDraw::unknown_5e2160(window,(int)child);
            if(Compare_Wide_007837d3(text.Get(),guest_empty_wide_839d4c)==0)
                text=OwnerDraw::unknown_5e2260((unsigned)window,child);
        }
        SendMessageA(tooltip,0x4b2,0,(LPARAM)text.unknown_text_770430());
        return 0;
    }
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 2:
        if(unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8=0;
        }
        if(!ProgressScreen.Has_Window()) goto host_unhandled;
        ProgressScreen.Clear_Window();
        return 0;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        if(unknown_dialog_preview_a72ce8) unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        else if(unknown_session_a3d2b4==-1 && unknown_preview_a6fee4) unknown_preview_a6fee4->Draw_0061D460(window);
        if(ProgressScreen.Has_Window()) ProgressScreen.Draw_It(Point2D(-1,-1));
        ValidateRect(window,0);
        return 0;
    case 0x111: {
        int command=wparam&0xffff;
        switch(command) {
        case 2:
            if(unknown_b2ac40) goto host_unhandled;
            Save_Lobby_Options_005cc890(window,&unknown_session_a3d298.WonlineOptions);
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            if(unknown_dialog_preview_a72ce8) { delete unknown_dialog_preview_a72ce8; unknown_dialog_preview_a72ce8=0; }
            Unknown_007357E0(window,2); ShowWindow(window,0); unknown_dialog_5ecf40(window,1);
            unknown_chat_a72cfc->unknown_slot09(); host_leave_b2abf0=1;
            return 0;
        case 0x3ed: {
            HWND input=GetDlgItem(window,0x540);
            WideString text=Limit_Name_Text_005ccf50(input);
            SendMessageA(input,0x4b2,0,(LPARAM)guest_empty_wide_839d4c);
            SetFocus(input);
            InvalidateRect(input,0,0);
            int color=guest_action_color_7a7370;
            if(strlen(unknown_channel_b299c0.name)==0)
                Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9fc,0,wol_source_file_007fd62c,0x3ae5));
            else if(text.Length()>0) {
                if(Unknown_0073cb80(text)) color=guest_private_action_color_7a736c;
                Unknown_005C2C80(color,guest_label_7fe2c4,unknown_wstring_b26cb8.Buffer,text.Get());
            } else Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9e8,0,wol_source_file_007fd62c,0x3aec));
            return 0;
        }
        case 0x540: {
            wchar_t nickname[16],primary_command[64],alternate_command[64];
            WideString text=Limit_Name_Text_005ccf50((HWND)lparam);
            if((unsigned short)(wparam>>16)==0x501) {
                SendMessageA((HWND)lparam,0x4b2,0,(LPARAM)guest_empty_wide_839d4c);
                if(text.Length()>0) {
                    int parsed=Parse_Page_Command_00746480(text.Get());
                    if(parsed!=0) {
                        if(parsed==1) {
                            int count=0;
                            unsigned length=text.Length()+1;
                            wchar_t *copy=(wchar_t *)operator new(length*2);
                            wcscpy(primary_command,StringTable::Load_String(guest_label_7dfc7c,0,wol_source_file_007fd62c,0x3a71));
                            if(!copy) return 0;
                            copy=wcsncpy(copy,text.Get(),length);
                            if(!copy) return 0;
                            wchar_t *body=copy+wcslen(primary_command);
                            while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                            while(*body) {
                                if(wcsncmp(body,guest_label_7d64f4,1)==0 || count>10) break;
                                nickname[count++]=*body++;
                            }
                            nickname[count]=0;
                            while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                            if(count>10) Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9d4,0,wol_source_file_007fd62c,0x3a8f));
                            else if(count==0) Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc64,0,wol_source_file_007fd62c,0x3a91));
                            else if(wcslen(body)>0) Unknown_005C2C80(guest_private_color_7a7368,guest_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                            else Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc48,0,wol_source_file_007fd62c,0x3a97));
                            operator delete(copy);
                        }
                    } else if(Reply_To_Last_Pager_007466c0(text.Get())) {
                        unsigned length=text.Length()+1;
                        wchar_t *copy=(wchar_t *)operator new(length*2);
                        wcscpy(primary_command,StringTable::Load_String(guest_label_7dfc14,0,wol_source_file_007fd62c,0x3aa9));
                        wcscpy(alternate_command,StringTable::Load_String(guest_label_7dfbfc,0,wol_source_file_007fd62c,0x3aaa));
                        if(!copy) return 0;
                        copy=wcsncpy(copy,text.Get(),length);
                        if(!copy) return 0;
                        wchar_t *body=copy+(wcsncmp(copy,primary_command,wcslen(primary_command))==0 ? wcslen(primary_command):wcslen(alternate_command));
                        while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                        wcscpy(nickname,Unknown_006FA180(guest_last_pager_b2ac48));
                        if(wcslen(body)>0 && wcslen(nickname)>0)
                            Unknown_005C2C80(guest_private_color_7a7368,guest_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                        else if(wcslen(nickname)>0)
                            Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc48,0,wol_source_file_007fd62c,0x3ac7));
                        operator delete(copy);
                    } else if(!Parse_Online_Command_00746240(text.Get())) {
                        int color=guest_chat_color_7a737c;
                        if(Unknown_0073ca50(text)==1) color=guest_private_color_7a7368;
                        Unknown_005C2C80(color,guest_label_7fe9a4,unknown_wstring_b26cb8.Buffer,text.Get());
                    }
                }
            }
            return 0;
        }
        case 0x411: case 0x412: case 0x413: case 0x414:
        case 0x415: case 0x416: case 0x417: case 0x418:
            if((unsigned short)(wparam>>16)!=1 || unknown_b2ac40) goto host_unhandled;
            if(!Is_Host_005c86a0()) goto host_unhandled;
            { NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,command,-1); Unknown_005cbf20(window,command,entry,2); }
            return 0;
        case 0x522: case 0x523: case 0x524: case 0x525: case 0x526: case 0x527: case 0x528: case 0x6a2:
            if((unsigned short)(wparam>>16)!=1 || unknown_b2ac40) goto host_unhandled;
            Set_Slot_Color_005c9ab0(window,command);
            Unknown_005c3810(true,false); Refresh_Slot_Settings_005ca000(window,true);
            return 0;
        case 0x510: case 0x513: case 0x514: case 0x51e: case 0x51f: case 0x520: case 0x521: case 0x6a1:
            if((unsigned short)(wparam>>16)!=1 || unknown_b2ac40) goto host_unhandled;
            Set_Slot_Country_005c9a10(window,command);
            Unknown_005c3810(true,false); Refresh_Slot_Settings_005ca000(window,true);
            return 0;
        case 0x588: {
            SetFocus(GetDlgItem(window,0x540));
            if(unknown_b2ac04==1) goto host_unhandled;
            Save_Lobby_Options_005cc890(window,&unknown_session_a3d298.WonlineOptions);
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            Refresh_Slot_Settings_005ca000(window,true);
            int observers=0;
            for(int i=0;i<unknown_players_a3fa7c.Count();++i) if(unknown_players_a3fa7c[i]->Team==-1) ++observers;
            if(unknown_users_b2a728.Count-observers<2) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7e6b84,0,wol_source_file_007fd62c,0x397c)); return 0; }
            if(observers && unknown_session_a3d298.AICount) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec6c,0,wol_source_file_007fd62c,0x3987)); return 0; }
            bool missing=false;
            for(int j=1;j<unknown_players_a3fa7c.Count();++j) if(!unknown_players_a3fa7c[j]->unknown_map_state_6f) {
                Unknown_005C2C80(-1,StringTable::Load_String(host_label_7e6b74,0,wol_source_file_007fd62c,0x3992),unknown_players_a3fa7c[j],unknown_map_name_a3d342); missing=true;
            }
            if(missing) return 0;
            for(int k=0;k<unknown_users_b2a728.Count;++k) if(!unknown_player_b29cf0[k].unknown_20) {
                Unknown_005c3b70(); Unknown_005C2C80(-1,StringTable::Load_String(host_label_7e6b5c,0,wol_source_file_007fd62c,0x39a5)); return 0;
            }
            if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2) {
                if(unknown_users_b2a728.Count<(int)unknown_channel_b299c0.maxUsers) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec54,0,wol_source_file_007fd62c,0x39af),unknown_channel_b299c0.maxUsers); return 0; }
                int team1=0,team2=0;
                for(int q=0;q<unknown_users_b2a728.Count;++q) { if(unknown_player_b29cf0[q].unknown_18==0) ++team2; else ++team1; }
                if(team1!=team2) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec3c,0,wol_source_file_007fd62c,0x39be)); return 0; }
            }
            int limit=Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4);
            unsigned requested=SendDlgItemMessageA(window,0x552,0x400,0,0);
            if(limit<(int)((requested-observers)+unknown_users_b2a728.Count)) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7e24cc,0,wol_source_file_007fd62c,0x39c9),limit); return 0; }
            if(unknown_users_b2a728.Count>4) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec24,0,wol_source_file_007fd62c,0x39d1)); return 0; }
            MultiplayerGameMode *mode=unknown_session_a3d298.Mode;
            WideString error;
            if(!mode->unknown_slot5(&error)) {
                Unknown_005C2C80(-1,error.Get()); EnableWindow(GetDlgItem(Unknown_00735B10(),0x588),1); return 0;
            }
            if(Unknown_0073c3c0(&unknown_game_channel_b299c0)) {
                WOL::User *user=0;
                unsigned squad1=0,squad2=0;
                int count1=0,count2=0;
                char observer[10]="";
                if(unknown_lobby_flag_7e6d90>=0) {
                    NodeNameType *node=unknown_player_slots_a3fa98[unknown_lobby_flag_7e6d90];
                    if(Unknown_005c93a0(node) && node->Team==-1) { char *name=Unknown_006FA120(node->Name); strncpy(observer,name,10); observer[9]=0; }
                }
                for(int u=0;u<unknown_users_b2a728.Count;++u) {
                    unknown_users_b2a728.Get(user,u);
                    if(_stricmp(observer,user->name)) {
                        unsigned squad=user->unknown_14;
                        if(squad<1) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec10,0,wol_source_file_007fd62c,0x39fb)); return 0; }
                        if(!squad1 || squad1==squad) { squad1=squad; ++count1; }
                        else { if(squad2 && squad2!=squad) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec10,0,wol_source_file_007fd62c,0x3a0a)); return 0; } squad2=squad; ++count2; }
                    }
                }
                if(count1!=count2) { Unknown_005C2C80(-1,StringTable::Load_String(host_label_7fec10,0,wol_source_file_007fd62c,0x3a10)); return 0; }
            }
            mode->unknown_slot22(); unknown_session_a3d298.Unknown_00672BB0(); Unknown_0073c480();
            Unknown_005c3810(true,true); mode->unknown_slot21(); mode->unknown_slot9();
            WOL::User user; memset(&user,0,sizeof(user)); WOL::User *head=0;
            for(int v=0;v<unknown_users_b2a728.Count;++v) {
                unknown_users_b2a728.Get_Copy(user,v); WOL::User *next=new WOL::User; *next=user; next->next=head; head=next;
            }
            unknown_chat_a72cfc->RequestGameStart(head); unknown_b2ac40=1; unknown_b2ac04=true;
            WOL::User *current=head;
            while(current) { head=current->next; delete current; current=head; }
            return 0;
        }
        case 0x5aa: {
            if(unknown_b2ac40) goto host_unhandled;
            int old=unknown_session_a3d2b4;
            bool ai=!unknown_session_a3d298.Mode || unknown_session_a3d298.Mode->unknown_slot12();
            bool observers=!unknown_session_a3d298.Mode || unknown_session_a3d298.Mode->unknown_slot40();
            char filename[132]; wchar_t description[130];
            strcpy(filename,host_scenario_file_a3d8f0); wcscpy(description,unknown_map_name_a3d342);
            host_scenario_enabled_7e6dc0=false; Unknown_005e5150(window,false); unknown_5159b0(0,true);
            bool cancelled=Open_Lobby_Dialog_005c6960((HWND)unknown_b263d8)==2;
            ShowWindow(window,5); unknown_dialog_5ecf40(window,0); SetFocus(GetDlgItem(window,0x540));
            if(cancelled) {
                unknown_session_a3d2b4=old; Select_Scenario_005c7c30(old); Unknown_005c7570(window);
                host_scenario_enabled_7e6dc0=true; ShowWindow(window,5); unknown_dialog_5ecf40(window,0);
                Load_Random_Map_Preview_005cc800(window); Unknown_005c3810(true,false); InvalidateRect(window,0,0); return 0;
            }
            if(!Select_Scenario_005c7c30(unknown_session_a3d2b4)) unknown_session_a3d2b4=old;
            else {
                bool new_ai=!unknown_session_a3d298.Mode || unknown_session_a3d298.Mode->unknown_slot12();
                bool new_observers=!unknown_session_a3d298.Mode || unknown_session_a3d298.Mode->unknown_slot40();
                if(observers && !new_observers) Unknown_005cb560(window);
                if(ai && !new_ai) {
                    if(Unknown_Clear_Closed_Slots_005cacb0(window)) {
                        unknown_session_a3d298.AICount=0; Unknown_0073c480(); Unknown_0073FEE0(0,false); Unknown_005c3810(true,false);
                    } else Unknown_0073FEE0(0,true);
                }
                Change_Scenario_Slots_005cb8d0(window,old,unknown_session_a3d2b4);
            }
            Update_Channel_Player_Limit_00749f20(); host_scenario_enabled_7e6dc0=true;
            ShowWindow(window,5); unknown_dialog_5ecf40(window,0); Unknown_005c34b0(window);
            if(strcmp(filename,host_scenario_file_a3d8f0) || Compare_Wide_007837d3(description,unknown_map_name_a3d342)) {
                for(int accepted=(int)&unknown_player_b29cf0[1].unknown_20;accepted<(int)&unknown_player_b29cf0[8].unknown_20;accepted+=sizeof(WolPlayerData)) *(int *)accepted=0;
            }
            Unknown_Enable_Start_005c9700(); Load_Random_Map_Preview_005cc800(window); Refresh_Slot_Settings_005ca000(window,true); Unknown_005c3810(true,false); InvalidateRect(window,0,0);
            return 0;
        }
        }
        return 0;
    }
    case 0x497: {
        SendDlgItemMessageA(window,0x3ed,0x49c,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(guest_label_7eb2e4,0));
        SendDlgItemMessageA(window,0x3ed,0x4aa,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(guest_label_7eb2d8,0));
        MultiplayerGameMode *mode=MultiplayerGameMode::unknown_first_mode_5b6ec0();
        unknown_session_a3d298.GameModeIndex=mode->unknown_28; unknown_session_a3d298.Mode=mode;
        mode->unknown_slot8(); Unknown_005c3450(window,mode);
        unknown_session_a3d2b4=mode->unknown_slot13(); Select_Scenario_005c7c30(unknown_session_a3d2b4);
        Fill_Side_Combos_4d16d0(window); Init_Color_Entries_4d1ea0(); Fill_Color_Combos_4d2300(window);
        Select_Player_Side_4d1820(window,unknown_lobby_a3fa94); Select_Player_Color_4d23c0(window,unknown_lobby_a3fa94);
        Unknown_005cca30(window,&unknown_session_a3d298.WonlineOptions);
            Apply_Channel_Restrictions(window);
        if(unknown_session_a3d298.Mode && !unknown_session_a3d298.Mode->unknown_slot40()) {
            unknown_lobby_flag_7e6d90=-1; unknown_a72c68=0; Unknown_005cd540(0);
            unknown_players_a3fa7c[0]->Team=0;
            unknown_player_slots_a3fa98[0]->unknown_66e2d0(unknown_session_a3d298.Mode->unknown_slot10());
            unknown_player_slots_a3fa98[0]->unknown_66e300(-2); Fill_Color_Combos_4d2300(window);
        }
        Unknown_005c9b90(window,0,true); Change_Scenario_Slots_005cb8d0(window,-1,unknown_session_a3d2b4);
        Update_Channel_Player_Limit_00749f20(); Refresh_Slot_Images_005c9ec0(window);
        Unknown_005c3450(window,unknown_session_a3d298.Mode); Unknown_005c34b0(window); Load_Random_Map_Preview_005cc800(window);
        host_version_a3d8d4=version_object_00a40c88.Version_Number(); SetTimer(window,0x14af8,5000,0);
        Unknown_Fill_Options_Dialog_005c3550(window,1); Refresh_Slot_Settings_005ca000(window,true); SetFocus(GetDlgItem(window,0x540));
        if(unknown_b2ac40) goto host_unhandled;
        WOL::User user;
        memset(&user,0,sizeof(user));
        int count=unknown_users_b2a728.Count;
        int handle=0;
        int i=0;
        if(count>0) {
        do {
            unknown_users_b2a728.Get_Copy(user,i);
            unsigned long address=user.unknown_18;
            Debug_Printf(ping_request_debug_007fdde0,user.name,inet_ntoa(address));
            unknown_ladder_client_a72d00->Request_Ping(inet_ntoa(address),1000,&handle);
            ++i;
        } while(i<count);
        return 0;
        }
        goto host_unhandled;
    }
    case 0x114: case 0x115:
        if(!unknown_b2ac40) {
            unknown_session_a3d2d0=SendDlgItemMessageA(window,0x54f,0x400,0,0);
            unknown_session_a3d2bc=SendDlgItemMessageA(window,0x402,0x400,0,0);
            unknown_session_a3d298.GameSpeed_30=6-SendDlgItemMessageA(window,0x529,0x400,0,0);
            return 0;
        }
        goto host_unhandled;
    case 0x113: {
        if(wparam!=0x14af8 || !Is_Host_005c86a0()) goto host_unhandled;
        Unknown_0075b1b0();
        if(unknown_b2ac40) goto host_unhandled;
        WOL::User user;
        memset(&user,0,sizeof(user));
        int count=unknown_users_b2a728.Count;
        int handle=0;
        int i=0;
        if(count<=0) goto host_unhandled;
        do {
            unknown_users_b2a728.Get_Copy(user,i);
            unsigned long address=user.unknown_18;
            Debug_Printf(ping_request_debug_007fdde0,user.name,inet_ntoa(address));
            unknown_ladder_client_a72d00->Request_Ping(inet_ntoa(address),1000,&handle);
            ++i;
        } while(i<count);
        return 0;
    }
    case 0x49b:
        { HWND control=GetDlgItem(window,wparam); SendMessageA(control,0x4b3,0x7f,lparam); return 0; }
    case 0x4e9: {
        OwnerDraw::UnknownTextRequest *request=(OwnerDraw::UnknownTextRequest *)lparam;
        int id;
        {
            WideString &text=request->text;
            text=(wchar_t const *)0;
            if(!request->unknown_00) goto tooltip_done;
            id=GetDlgCtrlID((HWND)request->unknown_00);
            if(request->unknown_04!=-1) {
                if(Control_Slot_005c9800(id)==-1) {
                    if(Side_Combo_Player_4d13b0(id)==-1) {
                        if(Color_Combo_Player_4d1d10(id)!=-1) {
                            text=Color_Name_4d1d80(Color_Combo_Data_4d2900(window,id,request->unknown_04));
                            return 1;
                        }
                    } else {
                        int country=Side_Combo_Data_4d1c70(window,id,request->unknown_04);
                        if(country!=-1) { text=Side_Name_4d1420(country); return 1; }
                    }
                } else {
                    NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,id,request->unknown_04);
                    text=Entry_Type_Name_005c9870(entry);
                    return 1;
                }
                goto tooltip_done;
            }
            if(Control_Slot_005c9800(id)!=-1) {
                NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,id,-1);
                if(entry) {
                    WideString label=OwnerDraw::unknown_5e2260((unsigned)window,(HWND)request->unknown_00);
                    if((Compare_Wide_007837d3(label.Get(),StringTable::Load_String(guest_label_7e8fe8,0,wol_source_file_007fd62c,0x37dd))==0 ||
                        Compare_Wide_007837d3(label.Get(),StringTable::Load_String(guest_label_7e8e28,0,wol_source_file_007fd62c,0x37dd))==0) && Unknown_005c9320(entry))
                        label=Player_Info_Tooltip_0074a120(entry->Name);
                    text=label.Get();
                }
                goto tooltip_done;
            }
        }
        {
            int player;
            if(id==0x754) player=0;
            else if(id==0x755) player=1;
            else if(id==0x756) player=2;
            else if(id==0x757) player=3;
            else if(id==0x758) player=4;
            else if(id==0x759) player=5;
            else if(id==0x75a) player=6;
            else if(id==0x75b) player=7;
            else goto tooltip_done;
            WideString ping;
            int slot=Slot_Control_Id_005c97a0(player);
            if(slot!=-1) {
                NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,slot,-1);
                if(entry && Unknown_005c9320(entry)) {
                    ping=Unknown_0074a4e0(entry->Name);
                    request->text=ping;
                }
            }
        }
tooltip_done:
        return 1;
    }
    case 0x4ed:
        ShowWindow(window,0);
        unknown_dialog_5ecf40(window,1);
host_unhandled:
        return 0;
    case 3: case 0x18: goto host_unhandled;
    case 0x14: return 1;
    default: return 0;
    }
    return 0;
}

// @ref ?host_version_a3d8d4@@3KA=00a3d8d4
// @ref ?host_scenario_enabled_7e6dc0@@3_NA=007e6dc0
// @ref ?host_scenario_file_a3d8f0@@3PADA=00a3d8f0
// @ref ?host_label_7fec10@@3PADA=007fec10
// @ref ?host_label_7fec24@@3PADA=007fec24
// @ref ?host_label_7e24cc@@3PADA=007e24cc
// @ref ?host_label_7fec3c@@3PADA=007fec3c
// @ref ?host_label_7e6b5c@@3PADA=007e6b5c
// @ref ?host_label_7fec54@@3PADA=007fec54
// @ref ?host_label_7e6b74@@3PADA=007e6b74
// @ref ?host_label_7fec6c@@3PADA=007fec6c
// @ref ?host_label_7e6b84@@3PADA=007e6b84
// @ref ?host_leave_b2abf0@@3HA=00b2abf0
// @ref ?Unknown_005c93a0@@YI_NPAUNodeNameType@@@Z=005c93a0
// @ref ?Unknown_005cca30@@YIXPAUHWND__@@PAUUnknownGameOptions@@@Z=005cca30
// @ref ?Unknown_005e5150@@YIXPAUHWND__@@_N@Z=005e5150
// @ref ?unknown_b299e0@@3IA=00b299e0
// @ref _inet_ntoa@4=00781b8a

// @ref ??_C@_00A@?$AA@=0083c55c
