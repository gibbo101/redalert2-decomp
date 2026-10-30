#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
void __fastcall unknown_dialog_5e5f20(HWND);
extern HANDLE wol_wait_events_b264f8[18];
extern char wol_start_command1_00800324[],wol_start_command2_00800378[];
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_start_command1_00800324@@3PADA=00800324
// @ref ?wol_start_command2_00800378@@3PADA=00800378
int __stdcall Wonline_Waiting_Dialog_0075c350(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message) {
    case 2:
        KillTimer(window,0);
        return 0;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 1;
    case 0x14:
        return 1;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 0x5c0:
            if(unknown_b26898==11) Unknown_007357E0(window,0);
            else SetEvent(wol_wait_events_b264f8[0]);
            break;
        case 0x708:
            unknown_chat_a72cfc->unknown_slot11(wol_start_command1_00800324);
            break;
        case 0x709:
            unknown_chat_a72cfc->unknown_slot11(wol_start_command2_00800378);
            break;
        }
        return 0;
    case 0x113:
        if(wparam==0) Add_Chat_Dot_005c3040();
        return 0;
    case 0x497:
        SetTimer(window,0,2000,0);
        return 0;
    }
    return 0;
}
