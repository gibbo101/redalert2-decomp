#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern HANDLE wol_wait_events_b264f8[18];
extern bool connection_wait_callback_0073c120();
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
inline void __fastcall Close_Wonline_Wait(unsigned int);
extern char wol_wdt_error_007fe4c0[],wol_fetch_wdt_007ff994[],wol_source_file_007fd62c[];
extern char wol_wdt_endpoint_007ff9c8[],wol_wdt_current_007ff9a8[],wol_wdt_previous_007ff978[];
// @ref ?wol_wdt_error_007fe4c0@@3PADA=007fe4c0
// @ref ?wol_fetch_wdt_007ff994@@3PADA=007ff994
// @ref ?wol_wdt_endpoint_007ff9c8@@3PADA=007ff9c8
// @ref ?wol_wdt_current_007ff9a8@@3PADA=007ff9a8
// @ref ?wol_wdt_previous_007ff978@@3PADA=007ff978
bool __fastcall Request_WDT_Cycle_00751df0()
{
    char const *connection=unknown_wdt_server_b29880.connection;
    if(connection==0) {
        Message_Box_005c3230(StringTable::Load_String(wol_wdt_error_007fe4c0,0,wol_source_file_007fd62c,0x5770),0,connection_wait_callback_0073c120,false);
        return false;
    } else {
    for(int i=0;i<18;++i) ResetEvent(wol_wait_events_b264f8[i]);
    HRESULT request=unknown_ladder_client_a72d00->Request_WDT_State(unknown_wdt_address_b269ac,unknown_wdt_port_b299bc,3);
    Debug_Printf(wol_wdt_endpoint_007ff9c8,unknown_wdt_address_b269ac,unknown_wdt_port_b299bc);
    Debug_Printf(wol_wdt_current_007ff9a8);
    if(request!=0) {
        Message_Box_005c3230(StringTable::Load_String(wol_wdt_error_007fe4c0,0,wol_source_file_007fd62c,0x5780),0,connection_wait_callback_0073c120,false);
        return false;
    } else {
    {
        WideString title(StringTable::Load_String(wol_fetch_wdt_007ff994,0,wol_source_file_007fd62c,0x5784));
        Open_Wait_Window_0074d4d0(0x10,title,false);
    }
    for(;;) {
        DWORD event;
        {
        int remaining=30000;
        event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
        while(event==0x102) {
            remaining-=100;
            if(remaining<=0) goto timeout;
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
        }
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==0) {
            Close_Wonline_Wait(~0U);
            return false;
        }
        if(event==5) {
            Message_Box_005c3230(StringTable::Load_String(wol_wdt_error_007fe4c0,0,wol_source_file_007fd62c,0x5797),0,connection_wait_callback_0073c120,false);
            Close_Wonline_Wait(~0U);
            return false;
        }
        if(event==18) {
timeout:
    Message_Box_005c3230(StringTable::Load_String(wol_wdt_error_007fe4c0,0,wol_source_file_007fd62c,0x579d),0,connection_wait_callback_0073c120,false);
    Close_Wonline_Wait(~0U);
            return false;
        }
        if(event==11) {
            request=unknown_ladder_client_a72d00->Request_WDT_State(unknown_wdt_address_b269ac,unknown_wdt_port_b299bc,5);
            Debug_Printf(wol_wdt_previous_007ff978);
            if(request!=0) {
                Close_Wonline_Wait(~0U);
                return false;
            } else {
                while(true) {
                    event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
                    while(event==0x102) {
                        Unknown_0073e100();
                        event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
                    }
                    ResetEvent(wol_wait_events_b264f8[event]);
                    if(event==0) {
                        Close_Wonline_Wait(~0U);
                        return false;
                    }
                    if(event==5) goto previous_cycle_error;
                    if(event==11) goto previous_cycle_success;
                }
previous_cycle_success:

                        Close_Wonline_Wait(~0U);
                        return true;
                    

previous_cycle_error:

                        Message_Box_005c3230(StringTable::Load_String(wol_wdt_error_007fe4c0,0,wol_source_file_007fd62c,0x57b8),0,connection_wait_callback_0073c120,false);
                        Close_Wonline_Wait(~0U);
                        return false;
                    
            }
        }
    }
    }
    }
    return false;
}
