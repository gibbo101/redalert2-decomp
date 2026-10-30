#include "shared/lobby.hpp"
#include "shared/win32_api.hpp"
extern int unknown_player_count_a3fa8c;
extern int unknown_player_controls_7fd334[8];
extern bool unknown_player_checked_b28dcc[8];
// @ref ?unknown_player_count_a3fa8c@@3HA=00a3fa8c
// @ref ?unknown_player_controls_7fd334@@3PAHA=007fd334
// @ref ?unknown_player_checked_b28dcc@@3PA_NA=00b28dcc
void __fastcall Mark_Player_Checked_0074dab0(int index)
{
    if(index>=0 && index<unknown_player_count_a3fa8c) {
        HWND dialog=(HWND)Unknown_00735940(0x12c);
        if(dialog) {
            HWND control=GetDlgItem(dialog,unknown_player_controls_7fd334[index]);
            unknown_player_checked_b28dcc[index]=true;
            SendMessageA(control,0xf1,1,0);
            PostMessageA(dialog,0xf,0,0);
        }
    }
}
