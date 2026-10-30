#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE*,BOOL,DWORD);
extern HANDLE wol_wait_events_b264f8[18];
extern char wol_logout_label_007fe478[],wol_source_file_007fd62c[];
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
// @ref __imp__WaitForMultipleObjects@16=0079a134
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_logout_label_007fe478@@3PADA=007fe478
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
void __fastcall Logout_Wonline_00741ea0()
{
    unknown_b2abd8=true;
    if(unknown_game_mode_a3d298==4 && unknown_a3d2a4==2) unknown_known_names_b294b8.Clear();
    if(unknown_chat_a72cfc) {
        for(int i=0;i<18;++i) ResetEvent(wol_wait_events_b264f8[i]);
        Unknown_0073e100();
        if(unknown_chat_a72cfc->unknown_slot13()==0) {
            {
                WideString title(StringTable::Load_String(wol_logout_label_007fe478,0,wol_source_file_007fd62c,0x201c));
                Open_Wait_Window_0074d4d0(0x20,title,false);
            }
            for(int attempt=0;attempt<5;++attempt) {
                DWORD event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
                while(event==0x102) {
                    Unknown_0073e100();
                    event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
                }
                ResetEvent(wol_wait_events_b264f8[event]);
                if(event==0 || event==9) break;
            }
        }
        void *dialog=Unknown_00735940(0x11e);
        if(dialog) Unknown_007357E0(dialog,0);
        void *wait=Unknown_00735940(0xc4);
        if(wait && !(unknown_b2abe0&=~0x20)) Unknown_007357E0(wait,0);
        HWND current=Unknown_00735B10();
        HWND edit=GetDlgItem(current,0x540);
        if(edit) SetFocus(edit);
    }
}
