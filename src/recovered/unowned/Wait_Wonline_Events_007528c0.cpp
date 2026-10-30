#include "shared/lobby.hpp"
#include "shared/win32_api.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE*,BOOL,DWORD);
// @ref __imp__WaitForMultipleObjects@16=0079a134
extern HANDLE wol_wait_events_b264f8[18];
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
DWORD __fastcall Wait_Wonline_Events_007528c0(int seconds,DWORD count)
{
    int remaining=seconds*1000;
    DWORD result=WaitForMultipleObjects(count,wol_wait_events_b264f8,0,100);
    while(result==0x102) {
        remaining-=100;
        if(remaining<=0) return 18;
        Unknown_0073e100();
        result=WaitForMultipleObjects(count,wol_wait_events_b264f8,0,100);
    }
    ResetEvent(wol_wait_events_b264f8[result]);
    return result;
}
