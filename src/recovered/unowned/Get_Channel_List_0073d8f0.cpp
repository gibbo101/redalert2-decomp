#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/debug_printf.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE*,BOOL,DWORD);
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
extern HANDLE wol_wait_events_b264f8[18];
extern char wol_channel_list_label_007fd754[],wol_connect_failed_label_007fd740[],wol_wait_failed_007fd708[],wol_source_file_007fd62c[];
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
// @ref __imp__WaitForMultipleObjects@16=0079a134
// @ref _swprintf=00783764
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_channel_list_label_007fd754@@3PADA=007fd754
// @ref ?wol_connect_failed_label_007fd740@@3PADA=007fd740
// @ref ?wol_wait_failed_007fd708@@3PADA=007fd708
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
inline void __fastcall Close_Wonline_Wait(unsigned int flags)
{
    void *wait=Unknown_00735940(0xc4);
    if(wait && !(unknown_b2abe0&=~flags)) Unknown_007357E0(wait,0);
    HWND current=Unknown_00735B10();
    HWND edit=GetDlgItem(current,0x540);
    if(edit) SetFocus(edit);
}
bool __fastcall Get_Channel_List_0073d8f0()
{
    {
        WideString title(StringTable::Load_String(wol_channel_list_label_007fd754,0,wol_source_file_007fd62c,0x7fa));
        Open_Wait_Window_0074d4d0(1,title,false);
    }
    int elapsed=0;
    for(;;) {
        DWORD event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        while(event==0x102) {
            elapsed+=100;
            if(elapsed>30000) {
                swprintf(unknown_server_error_b2a8ec,StringTable::Load_String(wol_connect_failed_label_007fd740,0,wol_source_file_007fd62c,0x803));
                SetEvent(wol_wait_events_b264f8[0]);
                return false;
            }
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        }
        if(event==(DWORD)-1) {
            Close_Wonline_Wait(1);
            Debug_Printf(wol_wait_failed_007fd708);
            return false;
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==5) {
            Close_Wonline_Wait(1);
            return false;
        }
        if(event==0) {
            Close_Wonline_Wait(1);
            break;
        }
        if(event==3) {
            Close_Wonline_Wait(1);
            return true;
        }
    }
    return false;
}
