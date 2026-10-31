#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
namespace OwnerDraw { void __fastcall unknown_5e6390(HWND); }
extern int unknown_player_controls_7fd334[8];
extern bool unknown_player_checked_b28dcc[8];
extern bool unknown_player_ready_b28dc4[9];
// @ref ?unknown_5e6390@OwnerDraw@@YIXPAUHWND__@@@Z=005e6390
// @ref ?unknown_player_controls_7fd334@@3PAHA=007fd334
// @ref ?unknown_player_checked_b28dcc@@3PA_NA=00b28dcc
// @ref ?unknown_player_ready_b28dc4@@3PA_NA=00b28dc4
long __stdcall Player_Readiness_Dialog_0074db40(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        ValidateRect(window,0);
        return 0;
    case 0x14:
        return 1;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        wparam &= 0xffff;
        switch(wparam) {
        case 0x761: case 0x762: case 0x764: case 0x765:
        case 0x766: case 0x767: case 0x768: case 0x769:
            if(unknown_player_ready_b28dc4[wparam-0x761]) {
                if(SendDlgItemMessageA(window,wparam,0xf0,0,0)==0)
                    SendDlgItemMessageA(window,wparam,0xf1,1,0);
            } else {
                if(SendDlgItemMessageA(window,wparam,0xf0,0,0)==1) {
                    SendDlgItemMessageA(window,wparam,0xf1,0,0);
                    return 0;
                }
            }
        }
        break;
    case 0x132: case 0x133: case 0x134: case 0x135:
    case 0x136: case 0x137: case 0x138:
        return (long)GetStockObject(4);
    case 0x497:
        for(int i=0;i<8;++i) {
            HWND control=GetDlgItem(window,unknown_player_controls_7fd334[i]);
            memset(unknown_player_checked_b28dcc,0,8);
            if(i>unknown_players_a3fa7c.Count()-1) DestroyWindow(control);
        }
        for(int player=0;player<unknown_players_a3fa7c.Count();++player) {
            HWND control=GetDlgItem(window,unknown_player_controls_7fd334[player]);
            SendMessageA(control,0x4b2,0,(LPARAM)unknown_players_a3fa7c[player]->Name);
            SendMessageA(control,0xf1,0,0);
        }
        SendMessageA(window,0x4a9,0,1);
        OwnerDraw::unknown_5e6390(window);
        ShowWindow(window,5);
        break;
    }
    return 0;
}
