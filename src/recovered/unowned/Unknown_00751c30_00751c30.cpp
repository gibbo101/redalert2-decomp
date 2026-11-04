// Server list wait00751C30: native two-event completion, error ranges and dialog cleanup.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE*,BOOL,DWORD);
extern HANDLE wol_wait_events_b264f8[18];
extern int server_request_status_b2ac00;
extern unsigned long wol_server_product_007fd370;
extern char account_text_7fe800[],account_text_7fe808[],account_text_7fd740[],wol_source_file_007fd62c[];
extern bool connection_wait_callback_0073c120();
// @ref __imp__WaitForMultipleObjects@16=0079a134
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?server_request_status_b2ac00@@3HA=00b2ac00
// @ref ?wol_server_product_007fd370@@3KA=007fd370
// @ref ?account_text_7fe800@@3PADA=007fe800
// @ref ?account_text_7fe808@@3PADA=007fe808
// @ref ?account_text_7fd740@@3PADA=007fd740
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
int __fastcall Unknown_00751c30(unsigned int flags)
{
    bool previous=unknown_b2abd8;
    unknown_b2abd8=true;
    unknown_servers_b2a700.Count=0;
    unknown_irc_index_b292d8=0;
    unknown_irc_index_b2a7f4=0;
    unknown_chat_a72cfc->Request_Server_List(unknown_b2ac5c|flags,0x10006,account_text_7fe800,account_text_7fe808,30);
    unknown_chat_a72cfc->unknown_slot35(wol_server_product_007fd370);
    bool servers=false;
    bool products=false;
    int result;
    DWORD event;
    for(;;) {
        event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,50);
        while(event==0x102) {
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,50);
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==0) break;
        if(event==8) break;
        if(event==1) {
            servers=true;
            if(products) goto complete;
        } else if(event==9) {
            int status=server_request_status_b2ac00;
            if(status<=(int)0x8004006d) {
                if(status>=(int)0x8004006c || (status>=(int)0x80040067 && status<=(int)0x8004006a)) {
                    Message_Box_005c3230(StringTable::Load_String(account_text_7fd740,0,wol_source_file_007fd62c,0x5739),0,connection_wait_callback_0073c120,false);
                    event=0;
                    break;
                }
            } else if(status==0x4012f) {
                products=true;
                if(servers) goto complete;
            }
        }
    }
    if(event==8) result=2;
    else result=1;
    goto cleanup;
complete:
    result=0;
cleanup:
    void *wait=Unknown_00735940(0xc4);
    if(wait) {
        unknown_b2abe0=0;
        Unknown_007357E0(wait,0);
    }
    HWND current=Unknown_00735B10();
    HWND edit=GetDlgItem(current,0x540);
    if(edit) {
        SetFocus(edit);
        unknown_b2abd8=previous;
        return result;
    }
    unknown_b2abd8=previous;
    return result;
}
