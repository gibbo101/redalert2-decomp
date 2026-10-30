#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
void __fastcall Wait_Paint_005e5f20(HWND window);
void __fastcall Unknown_005e6390(HWND window);
extern unsigned int wol_wait_delay_7fd384;
extern char wol_wait_url_7fecb4[];
// @ref ?Wait_Paint_005e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?Unknown_005e6390@@YIXPAUHWND__@@@Z=005e6390
// @ref ?wol_wait_delay_7fd384@@3IA=007fd384
// @ref ?wol_wait_url_7fecb4@@3PADA=007fecb4
long __stdcall Wonline_Wait_Dialog_0074d5e0(HWND window,unsigned message,unsigned wparam,long lparam)
{
    switch(message) {
    case 2:
        KillTimer(window,0x45);
        break;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0xf:
        Unknown_005FEE70(window);
        Wait_Paint_005e5f20(window);
        ValidateRect(window,0);
        break;
    case 0x14:
        return 1;
    case 0x110:
        return 0;
    case 0x111:
        switch(wparam & 0xffff) {
        case 0x58d:
            SetEvent(unknown_server_error_event_b264f8);
            Unknown_007357E0(window,1);
            break;
        case 0x58e:
            unknown_open_url_73c580(wol_wait_url_7fecb4,0);
            break;
        }
        break;
    case 0x113:
        if(wparam==0x45) {
            ShowWindow(window,5);
            KillTimer(window,0x45);
        }
        break;
    case 0x497:
        SendMessageA(window,0x4a9,0,1);
        SetTimer(window,0x45,wol_wait_delay_7fd384,0);
        Unknown_005e6390(window);
        break;
    }
    return 0;
}
