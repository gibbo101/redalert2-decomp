#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/id_source.hpp"
#include "shared/network_statistics.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
WIN32_IMPORT BOOL WINAPI GetComputerNameA(char *,DWORD *);
void __fastcall Unknown_007513e0();
void __fastcall Unknown_007514d0();
void __fastcall Unknown_007515b0();
extern int test_network_ids_007f60d0[];
extern int test_network_end_flag_00a40d2c;
extern char test_host1_007ff96c[],test_host2_007ff960[],test_master_name_007ff954[];
extern char test_start_debug_007fded4[],test_max_ping_debug_007e38bc[],test_no_ping_debug_007e38a0[];
extern char test_precalc_debug_007ff334[],test_frame_rate_debug_007ff314[],test_latency_debug_007d68f4[],test_send_rate_debug_007ff2fc[];
// @ref __imp__GetComputerNameA@8=0079a18c
// @ref ?test_network_ids_007f60d0@@3PAHA=007f60d0
// @ref ?test_network_end_flag_00a40d2c@@3HA=00a40d2c
// @ref ?test_host1_007ff96c@@3PADA=007ff96c
// @ref ?test_host2_007ff960@@3PADA=007ff960
// @ref ?test_master_name_007ff954@@3PADA=007ff954
// @ref ?test_start_debug_007fded4@@3PADA=007fded4
// @ref ?test_max_ping_debug_007e38bc@@3PADA=007e38bc
// @ref ?test_no_ping_debug_007e38a0@@3PADA=007e38a0
// @ref ?test_precalc_debug_007ff334@@3PADA=007ff334
// @ref ?test_frame_rate_debug_007ff314@@3PADA=007ff314
// @ref ?test_latency_debug_007d68f4@@3PADA=007d68f4
// @ref ?test_send_rate_debug_007ff2fc@@3PADA=007ff2fc
// @ref ??_C@_0BA@FOMN@xxx?4xxx?4xxx?4xxx?$AA@=007e38d0
void __fastcall Start_Test_Network_Game_007516c0()
{
    unknown_b2a7fc=0;
    unknown_b2ab84=unknown_protocol_7fd370;
    unknown_b2a7ec=0;
    strcpy(unknown_b2a6d8,unknown_wstring_b26cb8.Get());
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    // Capacity comes from the original GetComputerNameA size argument (0x3F7).
    char computer_name[1015];
    DWORD computer_name_size=sizeof(computer_name);
    GetComputerNameA(computer_name,&computer_name_size);
    bool precalculate=false;
    if(!_stricmp(computer_name,test_host1_007ff96c)) {
        Unknown_007515b0();Unknown_007513e0();Unknown_007514d0();
        precalculate=true;
    } else {
        if(!_stricmp(computer_name,test_host2_007ff960)) {
            Unknown_007514d0();Unknown_007513e0();
        } else {
            Unknown_007513e0();Unknown_007514d0();
        }
        Unknown_007515b0();
    }
    PacketTransport->unknown_slot12();
    char address[32]="xxx.xxx.xxx.xxx";
    NetNumType network;
    NetNodeType node;
    int i;
    for(i=1;i<unknown_players_a3fa7c.Count();++i) {
        unknown_players_a3fa7c[i]->Address.Get_Address(network,node);
        PacketTransport->unknown_slot11(address,0);
    }
    unknown_b2ac40=2;
    Debug_Printf(test_start_debug_007fded4,unknown_session_a3d298.NumPlayers);
    Unknown_006FA0C0(unknown_session_a3d298.MasterPlayerName,test_master_name_007ff954,-1);
    unknown_session_a3d298.MasterPlayerID=-1;
    unknown_session_a3d298.unknown_124=0;
    unknown_a40d3c=1;
    unknown_house_setting_7d88d8=10;
    unknown_session_a3d298.UnitCount=10;
    unknown_session_a3d298.unknown_24=10000;
    unknown_session_a3d298.unknown_fog_a7=false;
    unknown_session_a3d298.unknown_28=true;
    unknown_session_a3d298.unknown_crates_29=true;
    unknown_session_a3d298.unknown_a8=true;
    unknown_session_a3d298.unknown_a4=true;
    unknown_session_a3d298.unknown_a5=false;
    unknown_session_a3d298.unknown_bases_20=true;
    unknown_session_a3d298.unknown_a6=false;
    unknown_session_a3d298.AICount=0;
    unknown_session_a3d298.unknown_difficulty_40=0;
    unknown_session_a3d298.unknown_2a=true;
    unknown_session_a3d298.unknown_2b=true;
    unknown_session_a3d298.unknown_2c=false;
    unknown_session_a3d298.unknown_34=true;
    unknown_session_a3d298.ScenarioIndex=1;
    unknown_session_a3d298.GameSpeed_30=0;
    Select_Scenario_005c7c30(1);
    unknown_session_a3d298.GameSpeed_30=2;
    unknown_a40b18=2;
    unknown_id_source_a3d290->TechLevel=unknown_session_a3d298.ScenarioIndex;
    unknown_session_a3d298.unknown_2cc=5;
    switch(unknown_session_a3d298.GameSpeed_30) {
    case 0:unknown_session_a3d298.MaxAhead_2c8=40;unknown_session_a3d298.unknown_2e8=60;unknown_session_a3d298.unknown_2cc=10;break;
    case 1:unknown_session_a3d298.MaxAhead_2c8=40;unknown_session_a3d298.unknown_2e8=45;unknown_session_a3d298.unknown_2cc=10;break;
    case 2:unknown_session_a3d298.MaxAhead_2c8=30;unknown_session_a3d298.unknown_2e8=30;break;
    case 3:unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=20;break;
    case 4:unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=15;break;
    case 5:unknown_session_a3d298.MaxAhead_2c8=20;unknown_session_a3d298.unknown_2e8=12;break;
    default:unknown_session_a3d298.MaxAhead_2c8=10;unknown_session_a3d298.unknown_2e8=10;break;
    }
    unknown_session_a3d298.unknown_2e4=0;
    if(!precalculate) unknown_session_a3d298.unknown_2e8=0;
    int maximum_ping=0;
    for(i=0;i<unknown_players_a3fa7c.Count();++i) if(unknown_pings_b2a734[i]>maximum_ping) maximum_ping=unknown_pings_b2a734[i];
    unknown_a3fba4=1;
    if(maximum_ping==0 || maximum_ping==1000) {
        unknown_session_a3d298.unknown_2e8=0;
        Debug_Printf(test_no_ping_debug_007e38a0);
    } else {
        Debug_Printf(test_max_ping_debug_007e38bc,maximum_ping);
        if(maximum_ping>1000) unknown_a3fba4=2;
        else if(maximum_ping<600) unknown_a3fba4=1;
        int ticks=60*maximum_ping/1000;
        ticks+=120*ticks/100;
        unknown_ipx_manager_a40978.Set_Timing(ticks,(unsigned long)-1,ticks*8,true);
        if(precalculate) {
            unknown_ipx_manager_a40978.unknown_slot18(5,(unsigned long)-1,120);
            switch(unknown_a3fba4) {
            case 0:case 1:unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.MaxAhead_2c8;break;
            case 2:unknown_session_a3d298.unknown_2e4=(unknown_session_a3d298.MaxAhead_2c8>>1)+unknown_session_a3d298.MaxAhead_2c8;break;
            case 3:unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.MaxAhead_2c8*2;break;
            }
            unknown_session_a3d298.unknown_2e4=unknown_session_a3d298.unknown_2e4/10*10;
        }
    }
    Debug_Printf(test_precalc_debug_007ff334,unknown_session_a3d298.unknown_2e4);
    Debug_Printf(test_frame_rate_debug_007ff314,unknown_session_a3d298.unknown_2e8);
    Debug_Printf(test_latency_debug_007d68f4,unknown_a3fba4);
    Debug_Printf(test_send_rate_debug_007ff2fc,unknown_session_a3d298.unknown_2cc);
    unknown_session_a3d298.unknown_2e0=unknown_session_a3d298.MaxAhead_2c8;
    memset(unknown_session_a3d298.unknown_2ec,0,sizeof(player_statistics_00a3d584));
    test_network_ids_007f60d0[0]=1234;
    unknown_a40b18=unknown_session_a3d298.GameSpeed_30;
    test_network_ids_007f60d0[1]=1235;test_network_ids_007f60d0[2]=1236;test_network_ids_007f60d0[3]=1237;
    test_network_end_flag_00a40d2c=0;
    unknown_squad_1_b2a820[0]=0;unknown_squad_2_b293d8[0]=0;
    Unknown_Pregame_Setup_005c74f0();
}
