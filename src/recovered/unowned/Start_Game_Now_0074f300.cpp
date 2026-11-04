#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/udp_interface.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/win32_window.hpp"
#include "shared/win_util.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_talk.hpp"
#include "shared/network_statistics.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
long __stdcall Player_Readiness_Dialog_0074db40(HWND,UINT,WPARAM,LPARAM);
bool __fastcall Connect_Player_Pairs_0074ef80();
int __fastcall Sync_Scenario_With_Guests_00750330(bool);
void Report_Connection_Errors_0074dd50();
bool __fastcall Unknown_00514EE0();
extern int wol_connection_status_b26a2c[8];
extern int unknown_b2ac2c,unknown_b2ab88;
extern long unknown_b2a8a4;
extern HANDLE game_exit_event_b26510,game_start_event_b26514;
extern bool use_router_a402d0;
extern int game_port_7f60dc;
// @ref ?Player_Readiness_Dialog_0074db40@@YGJPAUHWND__@@IIJ@Z=0074db40
// @ref ?Connect_Player_Pairs_0074ef80@@YI_NXZ=0074ef80
// @ref ?Sync_Scenario_With_Guests_00750330@@YIH_N@Z=00750330
// @ref ?Report_Connection_Errors_0074dd50@@YAXXZ=0074dd50
// @ref ?Unknown_00514EE0@@YI_NXZ=00514ee0
// @ref ?wol_connection_status_b26a2c@@3PAHA=00b26a2c
// @ref ?unknown_b2ac2c@@3HA=00b2ac2c
// @ref ?unknown_b2ab88@@3HA=00b2ab88
// @ref ?unknown_b2a8a4@@3JA=00b2a8a4
// @ref ?game_exit_event_b26510@@3PAXA=00b26510
// @ref ?game_start_event_b26514@@3PAXA=00b26514
// @ref ?use_router_a402d0@@3_NA=00a402d0
// @ref ?game_port_7f60dc@@3HA=007f60dc
extern char start_text_007ff3e8[];
// @ref ?start_text_007ff3e8@@3PADA=007ff3e8
extern char start_text_007ff3c4[];
// @ref ?start_text_007ff3c4@@3PADA=007ff3c4
extern char start_text_007ff3a0[];
// @ref ?start_text_007ff3a0@@3PADA=007ff3a0
extern char start_text_007ff38c[];
// @ref ?start_text_007ff38c@@3PADA=007ff38c
extern char start_text_007ff34c[];
// @ref ?start_text_007ff34c@@3PADA=007ff34c
extern char start_text_007ff334[];
// @ref ?start_text_007ff334@@3PADA=007ff334
extern char start_text_007ff314[];
// @ref ?start_text_007ff314@@3PADA=007ff314
extern char start_text_007d68f4[];
// @ref ?start_text_007d68f4@@3PADA=007d68f4
extern char start_text_007ff2fc[];
// @ref ?start_text_007ff2fc@@3PADA=007ff2fc
extern char start_text_007ff2d0[];
// @ref ?start_text_007ff2d0@@3PADA=007ff2d0
extern char start_text_007ff2b8[];
// @ref ?start_text_007ff2b8@@3PADA=007ff2b8
extern char start_text_007ff290[];
// @ref ?start_text_007ff290@@3PADA=007ff290
extern char start_text_007e38bc[];
// @ref ?start_text_007e38bc@@3PADA=007e38bc
extern char start_text_007fd62c[];
// @ref ?start_text_007fd62c@@3PADA=007fd62c
extern char start_text_007ec57c[];
// @ref ?start_text_007ec57c@@3PADA=007ec57c
extern char start_text_007ce9c0[];
// @ref ?start_text_007ce9c0@@3PADA=007ce9c0
void __fastcall Start_Game_Now_0074f300()
{
    Debug_Printf(start_text_007ff3e8);
    unknown_b2ac44=true;
    PacketTransport->Discard_In_Buffers();
    PacketTransport->Discard_Out_Buffers();
    memset(wol_connection_status_b26a2c,0xff,sizeof(wol_connection_status_b26a2c));
    void *dialog=unknown_create_dialog_735700(ProgramInstance,300,MainWindow,Player_Readiness_Dialog_0074db40,0);
    if(dialog) unknown_show_dialog_5ff7e0(dialog,300);
    for(int n=0;n<100;++n) Service_Game_IO_00481fb0();
    unknown_ipx_manager_a40978.unknown_527830(300);
    bool connected=Connect_Player_Pairs_0074ef80();
    if(!connected) {
        unknown_login_state_00b2abe4=0;
        WOL::User *owner=0;
        for(int i=0;i<unknown_users_b2a728.Count;++i) {
            unknown_users_b2a728.Get(unknown_user_b2a658,i);
            if(unknown_user_b2a658.flags&1) { owner=&unknown_user_b2a658; break; }
        }
        if(!owner || _stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())) Debug_Printf(start_text_007ff3c4);
    }
    int transfer=Sync_Scenario_With_Guests_00750330(connected);
    if(transfer) {
        Debug_Printf(start_text_007ff3a0);
        if(transfer==2) Message_Box_005c3230(StringTable::Load_String(start_text_007ec57c,0,start_text_007fd62c,0x474b),0,Unknown_0073c120,false);
        HWND wait=Find_Dialog_00735940(300);
        if(wait) End_Dialog_007357e0(wait,0);
        unknown_b2ac40=0;
        if(unknown_a3d2a4==2 || unknown_a3d2a4==1) {
            unknown_b2ac2c=0;
            unknown_b26898=11;
            unknown_b2ab88=-1;
            unknown_b2a8a4=time(0);
        }
        unknown_b2ac04=false;
        Report_Connection_Errors_0074dd50();
        Unknown_00514EE0();
        unknown_b2ac45=false;
        unknown_b2ac44=false;
        if(transfer!=2) return;
        unknown_b2abd9=true;
        Debug_Printf(start_text_007ff38c);
        SetEvent(game_exit_event_b26510);
        Debug_Printf(start_text_007ff34c);
        unknown_chat_a72cfc->unknown_slot09();
        return;
    }
    for(int i=0;i<unknown_session_a3d298.Players.Count();++i) {
        if(!unknown_session_a3d298.unknown_3022.unknown[i]) unknown_session_a3d298.unknown_3022.unknown[i]=(unsigned short)unknown_default_port_7f60d0;
    }
    WOL::User *owner=Unknown_0074DA60();
    if(owner) {
        for(int j=0;j<unknown_session_a3d298.Players.Count();++j) {
            if(!_stricmp(Unknown_006FA120(unknown_session_a3d298.Players[j]->Name),owner->name)) {
                unknown_session_a3d298.unknown_292c=unknown_session_a3d298.unknown_3022.unknown[j];
                break;
            }
        }
    }
    HWND wait=Find_Dialog_00735940(300);
    if(wait) End_Dialog_007357e0(wait,0);
    if(unknown_session_a3d298.Type!=4 || unknown_a3d2a4!=2) unknown_session_a3d298.unknown_124=0;
    unknown_session_a3d298.unknown_2cc=5;
    switch(unknown_session_a3d298.GameSpeed_30) {
    case 0: unknown_session_a3d298.MaxAhead_2c8=40;unknown_session_a3d298.unknown_2e8=60;unknown_session_a3d298.unknown_2cc=10;break;
    case 1: unknown_session_a3d298.MaxAhead_2c8=40;unknown_session_a3d298.unknown_2e8=45;unknown_session_a3d298.unknown_2cc=10;break;
    case 2: unknown_session_a3d298.MaxAhead_2c8=30;unknown_session_a3d298.unknown_2e8=30;break;
    case 3: unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=20;break;
    case 4: unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=15;break;
    case 5: unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=12;break;
    default: unknown_session_a3d298.MaxAhead_2c8=10;unknown_session_a3d298.unknown_2e8=10;break;
    }
    if(use_router_a402d0) unknown_session_a3d298.MaxAhead_2c8+=20;
    unknown_session_a3d298.unknown_2e4=0;
    owner=Unknown_0074DA60();
    if(!owner || _stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())) unknown_session_a3d298.unknown_2e8=0;
    int worst_ping=0;
    for(int p=0;p<8;++p) if(unknown_pings_b2a734[p]>worst_ping) worst_ping=unknown_pings_b2a734[p];
    if(use_router_a402d0) worst_ping*=2;
    unknown_session_a3d298.unknown_290c=1;
    if(worst_ping!=0 && worst_ping!=1000) {
        Debug_Printf(start_text_007e38bc,worst_ping);
        if(worst_ping>1000) unknown_session_a3d298.unknown_290c=2;
        else if(worst_ping<600) unknown_session_a3d298.unknown_290c=1;
        int timing=60*worst_ping/1000;
        timing+=120*timing/100;
        unknown_ipx_manager_a40978.Set_Timing(timing,(unsigned long)-1,timing*8,true);
        owner=Unknown_0074DA60();
        if(owner && !_stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())) {
            switch(unknown_session_a3d298.unknown_290c) {
            case 0:case 1:unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.MaxAhead_2c8;break;
            case 2:unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.MaxAhead_2c8+(unknown_session_a3d298.MaxAhead_2c8>>1);break;
            case 3:unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.MaxAhead_2c8*2;break;
            }
            unknown_session_a3d298.unknown_2e4=((unsigned int)unknown_session_a3d298.unknown_2e4/10)*10;
        }
    } else {
        Debug_Printf(start_text_007ff2d0);
        unknown_session_a3d298.unknown_2e4=(unknown_session_a3d298.MaxAhead_2c8/10)*10;
        if(unknown_session_a3d298.unknown_2e4<=10) unknown_session_a3d298.unknown_2e4=10;
    }
    Debug_Printf(start_text_007ff334,unknown_session_a3d298.unknown_2e4);
    Debug_Printf(start_text_007ff314,unknown_session_a3d298.unknown_2e8);
    Debug_Printf(start_text_007d68f4,unknown_session_a3d298.unknown_290c);
    Debug_Printf(start_text_007ff2fc,unknown_session_a3d298.unknown_2cc);
    unknown_session_a3d298.unknown_2e0=unknown_session_a3d298.MaxAhead_2c8;
    memset(unknown_session_a3d298.unknown_2ec,0,sizeof(player_statistics_00a3d584));
    unknown_a40b18=unknown_session_a3d298.GameSpeed_30;
    unknown_default_port_7f60d0=1234;
    unknown_port_7f60d4=1235;
    unknown_alternate_port_7f60d8=1236;
    game_port_7f60dc=1237;
    Frame=0;
    if(use_router_a402d0) unknown_OwnerTalkClass_00ab6d18.Wait_For_Router_Shutdown(2000,true);
    unknown_squad_1_b2a820[0]=0;
    unknown_squad_2_b293d8[0]=0;
    if(unknown_session_a3d298.Type==4) {
        bool squads=Unknown_0073c3a0();
        if(squads) {
            WOL::User *user=0;
            int first_squad=0;
            int second_squad=0;
            int i=0;
            if(unknown_users_b2a728.Count<=0) goto squads_done;
squad_next:
            {
                unknown_users_b2a728.Get(user,i);
                if(first_squad==0 || first_squad==(int)user->unknown_14) {
                    strcat(unknown_squad_1_b2a820,user->name);
                    strcat(unknown_squad_1_b2a820,start_text_007ce9c0);
                    first_squad=user->unknown_14;
                } else if(second_squad==0 || second_squad==(int)user->unknown_14) {
                    strcat(unknown_squad_2_b293d8,user->name);
                    strcat(unknown_squad_2_b293d8,start_text_007ce9c0);
                    second_squad=user->unknown_14;
                }
            
            }
            ++i;
            if(i<unknown_users_b2a728.Count) goto squad_next;
squads_done:;
        }
        if(unknown_a3d2a4==2) {
            WOL::User *user=0;
            for(int i=0;i<unknown_users_b2a728.Count;++i) {
                unknown_users_b2a728.Get(user,i);
                if(unknown_player_b29cf0[i].unknown_18==0) {
                    strcat(unknown_squad_1_b2a820,user->name);
                    strcat(unknown_squad_1_b2a820,start_text_007ce9c0);
                } else {
                    strcat(unknown_squad_2_b293d8,user->name);
                    strcat(unknown_squad_2_b293d8,start_text_007ce9c0);
                }
            }
        }
    }
    Debug_Printf(start_text_007ff2b8);
    SetEvent(game_start_event_b26514);
    if(unknown_a3d2a4==2 || unknown_a3d2a4==1) {
        unknown_b2ac2c=0;
        unknown_b26898=11;
        unknown_b2ab88=-1;
        unknown_b2a8a4=time(0);
    }
    unknown_b2abd9=true;
    Debug_Printf(start_text_007ff290);
    unknown_chat_a72cfc->unknown_slot09();
    Unknown_Pregame_Setup_005c74f0();
    unknown_b2ac45=false;
    unknown_b2ac44=false;
}
