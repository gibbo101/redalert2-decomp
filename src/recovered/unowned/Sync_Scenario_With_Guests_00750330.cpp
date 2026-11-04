#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/session_state.hpp"
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/win_util.hpp"
extern int scenario_packet_length_a3f808;
extern unsigned short scenario_product_a3f818;
extern int wol_connection_status_b26a2c[];
extern int wol_connection_limit_7fd324[];
void __fastcall Unknown_006fa0f0(char *,wchar_t const *,int);
// @ref ?scenario_packet_length_a3f808@@3HA=00a3f808
// @ref ?scenario_product_a3f818@@3GA=00a3f818
// @ref ?wol_connection_status_b26a2c@@3PAHA=00b26a2c
// @ref ?wol_connection_limit_7fd324@@3PAHA=007fd324
// @ref ?Unknown_006fa0f0@@YIXPADPBGH@Z=006fa0f0
extern char scenario_debug_007e6b38[];
// @ref ?scenario_debug_007e6b38@@3PADA=007e6b38
extern char scenario_debug_007ff8c0[];
// @ref ?scenario_debug_007ff8c0@@3PADA=007ff8c0
extern char scenario_debug_007ff89c[];
// @ref ?scenario_debug_007ff89c@@3PADA=007ff89c
extern char scenario_debug_007ff87c[];
// @ref ?scenario_debug_007ff87c@@3PADA=007ff87c
extern char scenario_debug_007ff860[];
// @ref ?scenario_debug_007ff860@@3PADA=007ff860
extern char scenario_debug_007ff840[];
// @ref ?scenario_debug_007ff840@@3PADA=007ff840
extern char scenario_debug_007ff828[];
// @ref ?scenario_debug_007ff828@@3PADA=007ff828
extern char scenario_debug_007ff804[];
// @ref ?scenario_debug_007ff804@@3PADA=007ff804
extern char scenario_debug_007ff7ec[];
// @ref ?scenario_debug_007ff7ec@@3PADA=007ff7ec
extern char scenario_debug_007ff7d0[];
// @ref ?scenario_debug_007ff7d0@@3PADA=007ff7d0
bool Local_User_Is_Channel_Owner_0074d960();
int __fastcall Sync_Scenario_With_Guests_00750330(bool connected)
{
    UnknownGlobalPacket packet;
    bool failed=!connected;
    bool scenario_mismatch=false;
    int result=0;
    unknown_ipx_manager_a40978.unknown_5277f0();
    unknown_ipx_manager_a40978.Set_Timing(50,(unsigned long)-1,5000,true);
    WOL::User *owner;
    if(Local_User_Is_Channel_Owner_0074d960()) {
        memset(&packet,0,sizeof(packet));
        int responses[8];
        memset(responses,0,sizeof(responses));
        int num_responses=0;
        bool send_scenario=false;
        Debug_Printf(scenario_debug_007e6b38);
        CDTimerClass<SystemTimerClass> response_timer;
        response_timer=900;
        if(failed) response_timer=300;
        do {
            Service_Game_IO_00481fb0();
            if(unknown_ipx_manager_a40978.Get_Global_Message(&unknown_gpacket_a3f640,&scenario_packet_length_a3f808,&unknown_address_a3f80c,&scenario_product_a3f818) && scenario_product_a3f818==0xaa03) {
                Debug_Printf(scenario_debug_007ff8c0);
                for(int i=1;i<unknown_session_a3d298.Players.Count();++i) {
                    if(unknown_session_a3d298.Players[i]->Address.unknown_523690(unknown_address_a3f80c) && !_stricmp(Unknown_006FA120(unknown_session_a3d298.Players[i]->Name),unknown_gpacket_a3f640.Name) && !responses[i]) {
                        if(unknown_gpacket_a3f640.Command==16) {
                            Debug_Printf(scenario_debug_007ff89c);
                            responses[i]=unknown_gpacket_a3f640.Command;
                            send_scenario=true;
                            ++num_responses;
                        }
                        if(unknown_gpacket_a3f640.Command==19) {
                            Debug_Printf(scenario_debug_007ff87c);
                            responses[i]=unknown_gpacket_a3f640.Command;
                            ++num_responses;
                        }
                        if(unknown_gpacket_a3f640.Command==42) {
                            Debug_Printf(scenario_debug_007ff860);
                            responses[i]=unknown_gpacket_a3f640.Command;
                            ++num_responses;
                            failed=true;
                            if(i<unknown_session_a3d298.Players.Count() && wol_connection_status_b26a2c[i]<wol_connection_limit_7fd324[i]) wol_connection_status_b26a2c[i]=0;
                        }
                        if(unknown_gpacket_a3f640.Command==20) {
                            Debug_Printf(scenario_debug_007ff840);
                            responses[i]=unknown_gpacket_a3f640.Command;
                            result=2;
                            failed=true;
                            scenario_mismatch=true;
                            ++num_responses;
                        }
                    }
                }
            }
        } while(num_responses<unknown_session_a3d298.Players.Count()-1 && response_timer);
        if(scenario_mismatch) result=2;
        if(!failed && !scenario_mismatch && send_scenario && num_responses==unknown_session_a3d298.Players.Count()-1) {
            while(End_Dialog_007357e0(0,0)==1) {}
            memset(unknown_session_a3d298.ScenarioRequests,0,sizeof(unknown_session_a3d298.ScenarioRequests));
            unknown_session_a3d298.RequestCount=0;
            for(int j=1;j<unknown_session_a3d298.Players.Count();++j) {
                if(responses[j]==16) unknown_session_a3d298.ScenarioRequests[unknown_session_a3d298.RequestCount++]=(char)j;
            }
            if(!Send_Remote_File_0066bb20(unknown_id_source_a3d290->FileName,4,false,true)) {
                result=2;
                failed=false;
            }
        }
        memset(&packet,0,sizeof(packet));
        if(!failed && num_responses==unknown_session_a3d298.Players.Count()-1 && !scenario_mismatch) packet.Command=11;
        else {
            packet.Command=42;
            failed=true;
            if(!result) result=1;
        }
        Unknown_006fa0f0(packet.Name,unknown_session_a3d298.Players[0]->Name,-1);
        for(int k=1;k<unknown_session_a3d298.Players.Count();++k) {
            CDTimerClass<SystemTimerClass> send_timer(600);
            if(failed) send_timer=CDTimerClass<SystemTimerClass>(300);
            do {
                Service_Game_IO_00481fb0();
            } while(!unknown_ipx_manager_a40978.unknown_5259a0(&packet,47,1,unknown_session_a3d298.Players[k]->Name) && send_timer);
        }
    } else {
        if(Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658,unknown_session_a3d298.ScenarioFileLength_87c,unknown_session_a3d298.ScenarioDigest_85a,unknown_session_a3d298.ScenarioIsOfficial_880,true)) {
            memset(&packet,0,sizeof(packet));
            packet.Command=19;
            if(failed) packet.Command=42;
            Unknown_006fa0f0(packet.Name,unknown_session_a3d298.Players[0]->Name,-1);
            owner=0;
            for(int i=0;i<unknown_users_b2a728.Count;++i) {
                unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
                if(unknown_user_b2a658.flags&1) { owner=&unknown_user_b2a658; break; }
            }
            if(owner) unknown_ipx_manager_a40978.unknown_5259a0(&packet,47,1,Unknown_006FA180(owner->name));
            CDTimerClass<SystemTimerClass> send_timer;
            send_timer=1200;
            if(failed) send_timer=300;
            while(unknown_ipx_manager_a40978.Global_Num_Send()>0 && send_timer) Service_Game_IO_00481fb0();
        } else {
            if((unknown_a3d2a4!=2 && unknown_a3d2a4==1) || (unknown_session_a3d298.ScenarioIsOfficial_880 && !unknown_session_a3d298.Unknown_00672140())) {
                memset(&packet,0,sizeof(packet));
                packet.Command=20;
                owner=0;
                for(int i=0;i<unknown_users_b2a728.Count;++i) {
                    unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
                    if(unknown_user_b2a658.flags&1) { owner=&unknown_user_b2a658; break; }
                }
                if(owner) unknown_ipx_manager_a40978.unknown_5259a0(&packet,47,1,Unknown_006FA180(owner->name));
                Debug_Printf(scenario_debug_007ff828);
                CDTimerClass<SystemTimerClass> send_timer;
                send_timer=1200;
                while(unknown_ipx_manager_a40978.Global_Num_Send()>0 && send_timer) Service_Game_IO_00481fb0();
                result=2;
                failed=true;
            } else {
                while(End_Dialog_007357e0(0,0)==1) {}
                if(!Get_File_From_Host_0066aef0(unknown_session_a3d298.ScenarioFileName_658,4,true)) { result=2; failed=true; }
            }
        }
        strcpy(unknown_id_source_a3d290->FileName,unknown_session_a3d298.ScenarioFileName_658);
        Debug_Printf(scenario_debug_007ff804);
        CDTimerClass<SystemTimerClass> response_timer;
        response_timer=1200;
        if(failed) response_timer=300;
        do {
            Service_Game_IO_00481fb0();
            if(unknown_ipx_manager_a40978.Get_Global_Message(&unknown_gpacket_a3f640,&scenario_packet_length_a3f808,&unknown_address_a3f80c,&scenario_product_a3f818) && scenario_product_a3f818==0xaa03) {
                Debug_Printf(scenario_debug_007ff8c0);
                owner=0;
                for(int i=0;i<unknown_users_b2a728.Count;++i) {
                    unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
                    if(unknown_user_b2a658.flags&1) { owner=&unknown_user_b2a658; break; }
                }
                if(owner && !_stricmp(unknown_gpacket_a3f640.Name,owner->name)) {
                    if(unknown_gpacket_a3f640.Command==11) {
                        Debug_Printf(scenario_debug_007ff7ec);
                        goto finish;
                    }
                    if(unknown_gpacket_a3f640.Command==42) {
                        Debug_Printf(scenario_debug_007ff7d0);
                        failed=true;
                        for(int j=0;j<unknown_session_a3d298.Players.Count();++j) {
                            if(!_stricmp(Unknown_006FA120(unknown_session_a3d298.Players[j]->Name),unknown_user_b2a658.name)) {
                                if(j<unknown_session_a3d298.Players.Count() && wol_connection_status_b26a2c[j]<wol_connection_limit_7fd324[j]) wol_connection_status_b26a2c[j]=3;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        } while(response_timer);
        if(!response_timer) failed=true;
    }
finish:
    unknown_ipx_manager_a40978.Set_Timing(unknown_ipx_manager_a40978.unknown_526c30()+2,(unsigned long)-1,unknown_ipx_manager_a40978.unknown_526c30()*8<120?120:unknown_ipx_manager_a40978.unknown_526c30()*8,true);
    unknown_ipx_manager_a40978.unknown_527800();
    if(result!=2 && failed) result=1;
    return result;
}
