#include "shared/wol_sink.hpp"
#include "shared/firewall_settings.hpp"
#include "shared/session_state.hpp"
#include "shared/crt_string.hpp"
void Unknown_0074e470();
bool __fastcall Unknown_0074e5e0(int peer,int pair_slot,int step);
extern FirewallSettings wol_firewall_a71b18;
extern int unknown_player_controls_7fd334[8];
extern bool unknown_player_checked_b28dcc[8];
extern char wol_pair_debug_007ff270[],wol_wait_pair_007ff24c[],wol_pair_done_007ff1ac[];
extern char wol_wait_first_007ff218[],wol_wait_second_007ff1e4[],wol_wait_done_007ff1c8[];
// @ref ?Allocate_Ports_00673090@UnknownSessionState@@QAEXXZ=00673090
// @ref ?Unknown_0074e470@@YAXXZ=0074e470
// @ref ?Unknown_0074e5e0@@YI_NHHH@Z=0074e5e0
// @ref ?wol_firewall_a71b18@@3VFirewallSettings@@A=00a71b18
// @ref ?wol_pair_debug_007ff270@@3PADA=007ff270
// @ref ?wol_wait_pair_007ff24c@@3PADA=007ff24c
// @ref ?wol_pair_done_007ff1ac@@3PADA=007ff1ac
// @ref ?wol_wait_first_007ff218@@3PADA=007ff218
// @ref ?wol_wait_second_007ff1e4@@3PADA=007ff1e4
// @ref ?wol_wait_done_007ff1c8@@3PADA=007ff1c8
bool __fastcall Connect_Player_Pairs_0074ef80()
{
    CDTimerClass<SystemTimerClass> timer;
    unknown_session_a3d298.unknown_2f94=0;
    memset(unknown_session_a3d298.unknown_2ef4,0,sizeof(unknown_session_a3d298.unknown_2ef4));
    int pair_slot=-1;
    unknown_login_state_00b2abe4=0;
    if(unknown_session_a3d298.unknown_2dbc==0) return false;
    unknown_session_a3d298.Allocate_Ports_00673090();
    if(unknown_players_a3fa7c.Count()>0) {
        HWND window=(HWND)Unknown_00735940(300);
        if(window) {
            HWND control=GetDlgItem(window,unknown_player_controls_7fd334[0]);
            unknown_player_checked_b28dcc[0]=true;
            SendMessageA(control,0xf1,1,0);
            PostMessageA(window,0xf,0,0);
        }
    }
    for(int pair=0;pair<unknown_session_a3d298.unknown_2dbc;++pair) {
        int first=unknown_session_a3d298.unknown_29bc[pair*2];
        int second=unknown_session_a3d298.unknown_29bc[pair*2+1];
        int peer=-1;
        NodeNameType *first_player=unknown_player_slots_a3fa98[first];
        NodeNameType *second_player=unknown_player_slots_a3fa98[second];
        char const *first_name=Unknown_006FA120(first_player->Name);
        char const *second_name=Unknown_006FA120(second_player->Name);
        Debug_Printf(wol_pair_debug_007ff270,pair,first_name,second_name);
        char const *name=Unknown_006FA120(unknown_player_slots_a3fa98[first]->Name);
        if(_stricmp(name,unknown_wstring_b26cb8.Get())==0) {
            peer=second;
            pair_slot=pair*2+1;
            unknown_session_a3d298.unknown_2bbc[pair*2]=11;
        }
        name=Unknown_006FA120(unknown_player_slots_a3fa98[second]->Name);
        if(_stricmp(name,unknown_wstring_b26cb8.Get())==0) {
            peer=first;
            pair_slot=pair*2;
            unknown_session_a3d298.unknown_2bbc[pair*2+1]=11;
        }
        if(peer!=-1) {
            int step;
            if(wol_firewall_a71b18.Connection_Step_005baf20(unknown_session_a3d298.unknown_299c.unknown[first]) > wol_firewall_a71b18.Connection_Step_005baf20(unknown_session_a3d298.unknown_299c.unknown[second])) step=wol_firewall_a71b18.Connection_Step_005baf20(unknown_session_a3d298.unknown_299c.unknown[first]);
            else step=wol_firewall_a71b18.Connection_Step_005baf20(unknown_session_a3d298.unknown_299c.unknown[second]);
            if(!Unknown_0074e5e0(peer,pair_slot,step)) return false;
        } else {
            Debug_Printf(wol_wait_pair_007ff24c);
            timer=CDTimerClass<SystemTimerClass>(960);
            int progress=0;
            do {
                Sleep(5);
                Unknown_0073e100();
                Unknown_0074e470();
                int first_status=unknown_session_a3d298.unknown_2bbc[pair*2];
                int second_status=unknown_session_a3d298.unknown_2bbc[pair*2+1];
                if((first_status==11 || first_status==0) && (second_status==11 || second_status==0)) {
                    Debug_Printf(wol_wait_done_007ff1c8);
                    break;
                }
                if(first_status>=1 && first_status<11 && first_status-1>progress) {
                    Debug_Printf(wol_wait_first_007ff218,first_status-1);
                    progress=first_status-1;
                    timer=CDTimerClass<SystemTimerClass>(840);
                }
                if(second_status>=1 && second_status<11 && second_status-1>progress) {
                    Debug_Printf(wol_wait_second_007ff1e4,second_status-1);
                    progress=second_status-1;
                    timer=CDTimerClass<SystemTimerClass>(840);
                }
            } while(timer.Value()!=0);
        }
        if(unknown_session_a3d298.unknown_2bbc[pair*2]!=11) return false;
        if(unknown_session_a3d298.unknown_2bbc[pair*2+1]!=11) return false;
        Debug_Printf(wol_pair_done_007ff1ac);
    }
    return true;
}
